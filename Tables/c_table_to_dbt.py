#!/usr/bin/env python3
"""Generate a DBT file from C table definition pairs.

This script scans the current directory for matching `.h` and `.c` files.
For each pair it parses the table typedef found in the header and the
corresponding initializer in the source file. The information is written to a
single DBT file that roughly matches the style of `table_ACS.dbt`.

The heavy lifting of parsing C syntax is delegated to functions from
`extract_c_tables.py` which already exists in this repository. Only a small
subset of the DBT format is generated – each field gets a datatype and a
default value. Comments from the C initializer are used as descriptions when
present.

The resulting file is written next to this script as ``auto_tables.dbt``.
"""

from __future__ import annotations

import re
from pathlib import Path
from typing import Dict, List, Iterable

# Re-use the non-trivial parsing utilities from extract_c_tables.
from extract_c_tables import (
    read_text,
    build_header_nodes_tree,
    build_header_nodes,
    find_alias_initializers,
    collect_sv_variants,
    resolve_conditionals_for_variant,
    split_items_core_at_top,
    map_nodes_to_items_min,
    explode_index_and_value,
    comment_map_for_nodes,
)


def _rows_for_variant(nodes, inner: str, sv_value: str | None) -> List[Dict[str, str]]:
    """Return rows for one SV_ID variant."""
    inner_resolved = resolve_conditionals_for_variant(inner, sv_value)
    core_items = split_items_core_at_top(inner_resolved)
    flat_rows, _ = map_nodes_to_items_min(nodes, core_items)

    expanded: List[Dict[str, str]] = []
    for Type, Field, Index, Value in flat_rows:
        # Expand multi dimensional values into individual rows
        if Index and Value.strip().startswith("{"):
            for idx_path, v in explode_index_and_value(Index, Value):
                expanded.append({"Type": Type, "Field": Field, "Index": idx_path, "Value": v})
        else:
            expanded.append({"Type": Type, "Field": Field, "Index": Index, "Value": Value})

    # map comments from initializer
    c_map = comment_map_for_nodes(nodes, "{" + inner_resolved + "}")

    rows: List[Dict[str, str]] = []
    for item in expanded:
        idx = item["Index"]
        cmt = c_map.get((item["Field"], idx), "")
        if not cmt and idx:
            m = re.match(r"(\[\d+\])", idx)
            if m:
                cmt = c_map.get((item["Field"], m.group(1)), "") or cmt
        if not cmt:
            cmt = c_map.get((item["Field"], "*"), "")
        if sv_value is not None:
            suffix = f" (SV_ID={sv_value})"
        else:
            suffix = ""
        rows.append(
            {
                "Type": item["Type"],
                "Field": item["Field"],
                "Index": item["Index"],
                "Value": item["Value"],
                "Description": (cmt + suffix).strip(),
            }
        )
    return rows


def process_pair(h_path: Path, c_path: Path) -> Dict[str, List[Dict[str, str]]]:
    """Return mapping of table name -> rows for a header/source pair."""
    htxt = read_text(h_path)
    ctxt = read_text(c_path)
    typedef_nodes, table_aliases = build_header_nodes_tree(htxt)

    result: Dict[str, List[Dict[str, str]]] = {}
    for alias, body in table_aliases:
        nodes = typedef_nodes.get(alias)
        if nodes is None:
            nodes = build_header_nodes(body, typedef_nodes)
        rows: List[Dict[str, str]] = []
        inits = find_alias_initializers(ctxt, alias)
        for inner in inits:
            variants = collect_sv_variants(inner)
            for sv in variants:
                rows.extend(_rows_for_variant(nodes, inner, sv))
        if rows:
            result[alias] = rows
    return result


def discover_pairs(folder: Path) -> Iterable[tuple[Path, Path]]:
    hs = {p.stem: p for p in folder.glob("*.h")}
    cs = {p.stem: p for p in folder.glob("*.c")}
    for stem in sorted(hs.keys() & cs.keys()):
        yield hs[stem], cs[stem]


def dbt_from_tables(tables: Dict[str, List[Dict[str, str]]]) -> str:
    lines: List[str] = ["@gsw.subsystem: AUTO", "@classname: FC", ""]
    for tname, rows in sorted(tables.items()):
        lines.append(f"table {tname} {{")
        lines.append("  @buildstruct!")
        for row in rows:
            idx = row["Index"]
            field_name = f"{row['Field']}{idx}" if idx else row["Field"]
            lines.append(f"  .{field_name}:")
            lines.append(f"    @datatype: {row['Type']}")
            lines.append(f"    @default: {row['Value']}")
            if row["Description"]:
                lines.append(f"    @description: \"{row['Description']}\"")
            lines.append("")
        lines.append("}")
        lines.append("")
    return "\n".join(lines)


def main() -> None:
    folder = Path(__file__).resolve().parent
    all_tables: Dict[str, List[Dict[str, str]]] = {}
    for h, c in discover_pairs(folder):
        all_tables.update(process_pair(h, c))
    out_text = dbt_from_tables(all_tables)
    out_path = folder / "auto_tables.dbt"
    out_path.write_text(out_text, encoding="utf-8")
    print(f"Wrote: {out_path}")


if __name__ == "__main__":
    main()
