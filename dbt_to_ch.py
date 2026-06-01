#!/usr/bin/env python3
"""Generate C table source/header pairs from a DBT file.

The script keeps the generated C simple: one DBT table becomes one .h/.c pair,
and DBT-only details are saved beside the output as dbt_metadata.json. Helper
types such as uVector and uMatrix stay as project types instead of being
expanded by the generator.
"""

from __future__ import annotations

import argparse
import dataclasses
import json
import os
import re
import subprocess
import sys
import time
from collections import OrderedDict
from pathlib import Path
from typing import Any


SCRIPT_DIR = Path(__file__).resolve().parent
DEFAULT_DBT_FILE = SCRIPT_DIR / "Tables" / "table_ACS.dbt"
DEFAULT_OUTPUT_DIR = SCRIPT_DIR / "generated_from_dbt"

DBT_TO_C_TYPE = {
    "uint8": "uByte",
    "sint8": "byte",
    "int8": "byte",
    "uint16": "uWord",
    "sint16": "word",
    "int16": "word",
    "uint32": "uDword",
    "sint32": "dword",
    "int32": "dword",
    "float32": "float",
    "float48.ut69r": "dReal",
    "float64": "dReal",
    "data": "uByte",
}

HELPER_TYPES = {"uVector", "uMatrix", "uQuaternion", "lpf_param_type"}
VECTOR_MEMBERS = {"v": ("uVector", 3), "m": ("uMatrix", 3), "q": ("uQuaternion", 4)}
HEADER_COMMENT_COLUMN = 44
INITIALIZER_COMMENT_COLUMN = 42
COMPACT_INITIALIZER_LIMIT = 110


@dataclasses.dataclass
class DbtBlock:
    """One `.path:` block inside a DBT table."""

    path: str
    quoted: bool
    attrs: OrderedDict[str, str] = dataclasses.field(default_factory=OrderedDict)


@dataclasses.dataclass
class DbtTable:
    """A DBT table and the blocks declared inside it."""

    name: str
    attrs: OrderedDict[str, str] = dataclasses.field(default_factory=OrderedDict)
    blocks: list[DbtBlock] = dataclasses.field(default_factory=list)


@dataclasses.dataclass
class Segment:
    name: str
    indices: list[int] = dataclasses.field(default_factory=list)


@dataclasses.dataclass
class FieldNode:
    """A field in the generated C struct tree."""

    name: str
    c_type: str = "uWord"
    dims: list[str] = dataclasses.field(default_factory=list)
    children: "OrderedDict[str, FieldNode]" = dataclasses.field(default_factory=OrderedDict)
    comment: str | None = None
    attrs: OrderedDict[str, str] = dataclasses.field(default_factory=OrderedDict)
    explicit_type: bool = False

    @property
    def is_custom_struct(self) -> bool:
        return self.c_type not in c_primitive_types() and self.c_type not in HELPER_TYPES


@dataclasses.dataclass
class BuiltTable:
    table: DbtTable
    type_name: str
    fields: "OrderedDict[str, FieldNode]"
    defaults: OrderedDict[str, str]
    attrs_by_path: OrderedDict[str, OrderedDict[str, str]]


@dataclasses.dataclass
class InitEntry:
    value: Any
    comment: str | None = None


def parse_dbt(path: Path) -> list[DbtTable]:
    """Read just the DBT syntax the generator needs.

    DBT files carry a lot of project metadata. For C generation we only need
    table declarations, `.field:` blocks, and their `@attrs`.
    """

    tables: list[DbtTable] = []
    current_table: DbtTable | None = None
    current_block: DbtBlock | None = None

    for raw_line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        line = raw_line.rstrip()
        table_match = re.match(r"^table\s+([A-Za-z_][A-Za-z0-9_]*)\s*\{", line)
        if table_match:
            current_table = DbtTable(table_match.group(1))
            tables.append(current_table)
            current_block = None
            continue
        if current_table is None:
            continue
        if line.strip() == "}":
            current_table = None
            current_block = None
            continue

        block_match = re.match(r'\s+\.(?:"([^"]+)"|([^:]+)):\s*$', line)
        if block_match:
            quoted = block_match.group(1) is not None
            current_block = DbtBlock((block_match.group(1) or block_match.group(2)).strip(), quoted)
            current_table.blocks.append(current_block)
            continue

        attr_match = re.match(r"\s+@([A-Za-z0-9_.!-]+):?\s*(.*)$", line)
        if attr_match:
            key, value = attr_match.group(1), attr_match.group(2).strip()
            if current_block is None:
                current_table.attrs[key] = value
            else:
                current_block.attrs[key] = value

    return tables


def build_table(table: DbtTable) -> BuiltTable:
    """Turn a flat list of DBT blocks into a C-shaped field tree."""

    fields: OrderedDict[str, FieldNode] = OrderedDict()
    defaults: OrderedDict[str, str] = OrderedDict()
    attrs_by_path: OrderedDict[str, OrderedDict[str, str]] = OrderedDict()

    top_blocks = [block for block in table.blocks if is_top_field(block)]
    for block in top_blocks:
        c_type = dbt_type_to_c(block.attrs.get("datatype", "uint16"))
        attrs_by_path[block.path] = OrderedDict(block.attrs)
        fields[block.path] = FieldNode(
            name=block.path,
            c_type=c_type,
            dims=parse_array_attr(block.attrs.get("array")),
            comment=comment_from_attrs(block.attrs),
            attrs=OrderedDict(block.attrs),
            explicit_type=True,
        )
        if "default" in block.attrs:
            defaults[block.path] = dbt_default_to_c(block.attrs["default"])

    top_names = set(fields)
    for block in table.blocks:
        if is_wildcard(block.path):
            continue
        actual_path = actual_leaf_path(block, top_names)
        if not actual_path:
            continue
        attrs_by_path[actual_path] = OrderedDict(block.attrs)
        if "default" in block.attrs:
            defaults[actual_path] = dbt_default_to_c(block.attrs["default"])
        if actual_path in top_names:
            continue
        add_leaf_to_schema(fields, actual_path, block)

    return BuiltTable(
        table=table,
        type_name=table_type_name(table.name),
        fields=fields,
        defaults=defaults,
        attrs_by_path=attrs_by_path,
    )


def is_top_field(block: DbtBlock) -> bool:
    return (
        "datatype" in block.attrs
        and not block.quoted
        and "." not in block.path
        and "[" not in block.path
        and not is_wildcard(block.path)
    )


def is_wildcard(path: str) -> bool:
    return "[*" in path or path.endswith(".*")


def actual_leaf_path(block: DbtBlock, top_names: set[str]) -> str | None:
    """Return the C field path for a DBT block, or None when it is metadata only."""

    if block.quoted and is_wildcard(block.path):
        return None
    path = unquote_attr(block.attrs.get("structname", "")) if "structname" in block.attrs else block.path
    if is_wildcard(path):
        return None
    parts = split_path(path)
    if not parts:
        return None
    if parts[0].name in top_names:
        return path_from_segments(parts)
    if len(parts) > 1 and parts[1].name in top_names:
        return path_from_segments(parts[1:])
    if block.path and split_path(block.path) and split_path(block.path)[0].name in top_names:
        return block.path
    return path


def add_leaf_to_schema(fields: OrderedDict[str, FieldNode], path: str, block: DbtBlock) -> None:
    """Add one DBT leaf to the generated struct tree."""

    parts = split_path(path)
    if not parts:
        return
    top = fields.get(parts[0].name)
    if top is None:
        top = FieldNode(parts[0].name, c_type=infer_c_type(block), explicit_type=True)
        fields[top.name] = top

    node = top
    i = 1
    while i < len(parts):
        segment = parts[i]
        if segment.name in VECTOR_MEMBERS:
            # DBT exposes vector/matrix/quaternion internals as `.v`, `.m`, and
            # `.q`; the C headers keep the project helper type instead.
            node.c_type = VECTOR_MEMBERS[segment.name][0]
            node.explicit_type = True
            return

        child = node.children.get(segment.name)
        if child is None:
            child = FieldNode(segment.name)
            node.children[segment.name] = child
        merge_dims(child, segment.indices)
        child.comment = child.comment or comment_from_attrs(block.attrs)
        merge_attrs(child.attrs, block.attrs)

        next_segment = parts[i + 1] if i + 1 < len(parts) else None
        if next_segment and next_segment.name in VECTOR_MEMBERS:
            child.c_type = VECTOR_MEMBERS[next_segment.name][0]
            child.explicit_type = True
            return
        if next_segment:
            if not child.explicit_type:
                child.c_type = nested_type_name(node.c_type, child.name)
            node = child
            i += 1
            continue

        if not child.explicit_type:
            child.c_type = infer_c_type(block)
        merge_attrs(child.attrs, block.attrs)
        return


def merge_attrs(target: OrderedDict[str, str], source: OrderedDict[str, str]) -> None:
    for key, value in source.items():
        target.setdefault(key, value)


def merge_dims(node: FieldNode, indices: list[int]) -> None:
    for idx, value in enumerate(indices):
        needed = str(value + 1)
        if idx >= len(node.dims):
            node.dims.append(needed)
            continue
        if node.dims[idx].isdigit() and int(node.dims[idx]) < value + 1:
            node.dims[idx] = needed


def infer_c_type(block: DbtBlock) -> str:
    """Pick a safe C type when a nested DBT field omits `@datatype`."""

    if "datatype" in block.attrs:
        return dbt_type_to_c(block.attrs["datatype"])
    default = unquote_attr(block.attrs.get("default", "0"))
    if default in {"True", "False", "TRUE", "FALSE"}:
        return "uWord"
    if re.search(r"\d+\.\d*|\.\d+|\d+[Ee][+-]?\d+|DEG|RAD|PI", default):
        return "dReal"
    return "uWord"


def dbt_type_to_c(dbt_type: str) -> str:
    dbt_type = unquote_attr(dbt_type)
    return DBT_TO_C_TYPE.get(dbt_type, dbt_type)


def c_primitive_types() -> set[str]:
    return set(DBT_TO_C_TYPE.values()) | {"int", "unsigned int"}


def parse_array_attr(value: str | None) -> list[str]:
    if not value:
        return []
    value = unquote_attr(value)
    return [dbt_expr_to_c(part.strip()) for part in value.split(",") if part.strip()]


def split_path(path: str) -> list[Segment]:
    """Split `foo[0].bar` into named path parts with numeric indexes."""

    result: list[Segment] = []
    for raw_part in path.split("."):
        if not raw_part:
            continue
        name_match = re.match(r"([A-Za-z_][A-Za-z0-9_]*)", raw_part)
        if not name_match:
            continue
        indices = [int(idx) for idx in re.findall(r"\[(\d+)\]", raw_part)]
        result.append(Segment(name_match.group(1), indices))
    return result


def path_from_segments(parts: list[Segment]) -> str:
    chunks = []
    for part in parts:
        indices = "".join(f"[{idx}]" for idx in part.indices)
        chunks.append(f"{part.name}{indices}")
    return ".".join(chunks)


def table_type_name(table_name: str) -> str:
    return f"{name_to_snake(table_name)}_type"


def nested_type_name(parent_type: str, field_name: str) -> str:
    base = parent_type[:-5] if parent_type.endswith("_type") else parent_type
    return f"{base}_{name_to_snake(field_name)}_type"


def name_to_snake(name: str) -> str:
    if "_" in name and name.upper() == name:
        return name.lower()
    name = re.sub(r"([A-Z]+)([A-Z][a-z])", r"\1_\2", name)
    name = re.sub(r"([a-z0-9])([A-Z])", r"\1_\2", name)
    return name.lower()


def basename_for_table(table_name: str) -> str:
    return table_name.lower()


def comment_from_attrs(attrs: OrderedDict[str, str]) -> str | None:
    """Build a short field comment from DBT description/unit metadata."""

    desc = normalize_comment_text(attrs.get("description", ""))
    units = normalize_comment_text(attrs.get("units", ""))
    if desc == "":
        desc = ""
    if desc and units:
        if desc.lower().rstrip(" .").endswith(units.lower().rstrip(" .")):
            return desc
        return f"{desc}, {units}"
    return desc or units or None


def normalize_comment_text(value: str) -> str:
    value = unquote_attr(value).strip()
    value = value.replace("_", " ")
    value = re.sub(r"\s*,\s*", ", ", value)
    value = re.sub(r"\s+", " ", value)
    return value


def unquote_attr(value: str) -> str:
    value = value.strip()
    if len(value) >= 2 and value[0] == '"' and value[-1] == '"':
        return value[1:-1].replace('\\"', '"')
    return value


def dbt_default_to_c(value: str) -> str:
    value = dbt_expr_to_c(unquote_attr(value))
    if value == "True":
        return "TRUE"
    if value == "False":
        return "FALSE"
    return value


def dbt_expr_to_c(value: str) -> str:
    value = value.strip()
    value = re.sub(r"\bDBT_", "", value)
    value = value.replace("True", "TRUE").replace("False", "FALSE")
    value = re.sub(r"\b[A-Za-z_][A-Za-z0-9_]*\.([A-Za-z_][A-Za-z0-9_]*)\b", r"\1", value)
    return value


def render_header(built: BuiltTable) -> str:
    table = built.table
    guard = f"_{basename_for_table(table.name)}_h_"
    lines: list[str] = [
        "/*********************************************************************************************************************",
        " *",
        f" *  File:                {basename_for_table(table.name)}.h",
        " *",
        " *  Generated from DBT.",
        " *",
        " *********************************************************************************************************************/",
        "",
        "/************************************/",
        '#pragma pack()       /* Green Hills */',
        "/************************************/",
        "",
        f"#ifndef {guard}",
        f"#define {guard}",
        "",
        '#include "acstypes.h"',
        '#include "acsdefines.h"',
        "",
        "#pragma pack(4)",
        "",
    ]

    description = unquote_attr(table.attrs.get("description", "")).strip()
    if description:
        lines.extend(["/*", f"** {description} ...", "*/", ""])
    lines.extend(render_struct_typedef(built.type_name, built.fields))
    lines.extend(
        [
            "",
            f"#endif /* {guard} */",
            "",
            "/************************************/",
            '#pragma pack()       /* Green Hills */',
            "/************************************/",
            "",
        ]
    )
    return "\n".join(lines)


def render_struct_typedef(type_name: str, fields: OrderedDict[str, FieldNode]) -> list[str]:
    tag = type_name[:-5] if type_name.endswith("_type") else type_name
    lines = [f"typedef struct {tag}_ {{"]
    lines.extend(render_field_decls(list(fields.values()), indent="  "))
    lines.append(f"}} {type_name};")
    return lines


def render_field_decls(fields: list[FieldNode], indent: str) -> list[str]:
    simple_fields = [field for field in fields if not field_has_inline_struct(field)]
    type_width = max([len(field.c_type) for field in simple_fields] + [5]) + 2
    lines: list[str] = []
    previous_was_struct = False

    for field in fields:
        is_struct = field_has_inline_struct(field)
        if lines and (is_struct or previous_was_struct) and lines[-1] != "":
            lines.append("")
        if is_struct:
            lines.extend(render_inline_struct_decl(field, indent))
        else:
            lines.append(render_field_decl(field, indent, type_width))
        previous_was_struct = is_struct

    if lines and lines[-1] == "":
        lines.pop()
    return lines


def field_has_inline_struct(field: FieldNode) -> bool:
    return field.is_custom_struct and bool(field.children)


def render_inline_struct_decl(field: FieldNode, indent: str) -> list[str]:
    tag = field.c_type[:-5] if field.c_type.endswith("_type") else field.c_type
    lines = [f"{indent}struct {tag}_ {{"]
    lines.extend(render_field_decls(list(field.children.values()), indent=f"{indent}  "))
    dims = "".join(f"[{dim}]" for dim in field.dims)
    close = f"{indent}}} {field.name}{dims};"
    field_comment = render_field_comment(field)
    if field_comment:
        close = append_aligned_comment(close, f"/* {field_comment} */", HEADER_COMMENT_COLUMN)
    lines.append(close)
    return lines


def render_field_decl(field: FieldNode, indent: str, type_width: int) -> str:
    dims = "".join(f"[{dim}]" for dim in field.dims)
    field_comment = render_field_comment(field)
    decl = f"{indent}{field.c_type:<{type_width}}{field.name}{dims};"
    if not field_comment:
        return decl
    return append_aligned_comment(decl, f"/* {field_comment} */", HEADER_COMMENT_COLUMN)


def render_field_comment(field: FieldNode) -> str | None:
    return safe_comment(field.comment) if field.comment else None


def safe_comment(value: str) -> str:
    return str(value).replace("*/", "* /").replace("\n", " ").replace("\r", " ")


def render_source(built: BuiltTable, header_name: str) -> str:
    table = built.table
    description = unquote_attr(table.attrs.get("description", "")).strip()
    lines: list[str] = [
        "/*********************************************************************************************************************",
        " *",
        f" *  File:                {header_name[:-2]}.c",
        " *",
        " *  Generated from DBT.",
        " *",
        " *********************************************************************************************************************/",
        "",
    ]
    if description:
        lines.extend(["/*", f"** {description} ...", "*/", ""])
    lines.extend(
        [
            '#include "acstypes.h"',
            '#include "acsdefines.h"',
            f'#include "{header_name}"',
            "",
            f"{built.type_name} {table.name} =",
        ]
    )
    initializer = [
        InitEntry(render_field_value(field, field.name, built), initializer_comment(field.name, built))
        for field in built.fields.values()
    ]
    lines.append(format_initializer(initializer, 0) + ";")
    lines.append("")
    return "\n".join(lines)


def render_field_value(field: FieldNode, path: str, built: BuiltTable) -> Any:
    if field.dims:
        return render_array_value(field, path, built)
    if field.c_type == "uVector":
        return [render_indexed_member(path, "v", 3, built)]
    if field.c_type == "uMatrix":
        return [render_matrix_member(path, built)]
    if field.c_type == "uQuaternion":
        return [render_indexed_member(path, "q", 4, built)]
    if field.c_type == "lpf_param_type":
        return render_lpf(path, built)
    if field.is_custom_struct:
        if not field.children:
            return ["0"]
        return [
            InitEntry(
                render_field_value(child, f"{path}.{child.name}", built),
                initializer_comment(f"{path}.{child.name}", built),
            )
            for child in field.children.values()
        ]
    return built.defaults.get(path, "0")


def render_array_value(field: FieldNode, path: str, built: BuiltTable) -> Any:
    count = infer_array_count(path, built, field.dims)
    if count is None or count <= 0:
        return ["0"]
    element = dataclasses.replace(field, dims=field.dims[1:])
    return [
        render_field_value(element, f"{path}[{idx}]", built)
        for idx in range(count)
    ]


def infer_array_count(path: str, built: BuiltTable, dims: list[str]) -> int | None:
    """Choose how many array elements to emit in the initializer.

    Defaults win because they show what the DBT actually populated. Small fixed
    sizes are fine too. Very large symbolic arrays fall back to `{ 0 }` so the
    output does not balloon unexpectedly.
    """

    indexed = []
    prefix = re.escape(path)
    pattern = re.compile(rf"^{prefix}\[(\d+)\]")
    for default_path in built.defaults:
        match = pattern.match(default_path)
        if match:
            indexed.append(int(match.group(1)))
    if indexed:
        return max(indexed) + 1
    if dims and dims[0].isdigit():
        size = int(dims[0])
        if size <= 128:
            return size
    return None


def render_indexed_member(path: str, member: str, count: int, built: BuiltTable) -> Any:
    return [built.defaults.get(f"{path}.{member}[{idx}]", "0.0") for idx in range(count)]


def render_matrix_member(path: str, built: BuiltTable) -> Any:
    return [
        [built.defaults.get(f"{path}.m[{row}][{col}]", "0.0") for col in range(3)]
        for row in range(3)
    ]


def render_lpf(path: str, built: BuiltTable) -> Any:
    """Render the known layout for the project LPF helper type."""

    return [
        InitEntry(built.defaults.get(f"{path}.CascadeOrder", "0"), f"{path}.CascadeOrder"),
        InitEntry([built.defaults.get(f"{path}.SpareUWord[{idx}]", "0") for idx in range(3)], f"{path}.SpareUWord"),
        InitEntry(built.defaults.get(f"{path}.A0", "0.0"), f"{path}.A0"),
        InitEntry(
            [[built.defaults.get(f"{path}.A[{row}][{col}]", "0.0") for col in range(2)] for row in range(3)],
            f"{path}.A",
        ),
        InitEntry(
            [[built.defaults.get(f"{path}.B[{row}][{col}]", "0.0") for col in range(2)] for row in range(3)],
            f"{path}.B",
        ),
    ]


def initializer_comment(path: str, built: BuiltTable) -> str:
    return safe_comment(path)


def format_initializer(value: Any, indent: int) -> str:
    """Format nested C initializers with compact rows where they stay readable."""

    if isinstance(value, InitEntry):
        rendered = format_initializer(value.value, indent)
        if not value.comment:
            return rendered
        return append_initializer_comment(rendered, value.comment)
    if not isinstance(value, list):
        return str(value)
    compact = compact_initializer(value, indent)
    if compact is not None:
        return compact
    pad = "  " * indent
    child_pad = "  " * (indent + 1)
    lines = ["{"]
    for idx, item in enumerate(value):
        suffix = "," if idx < len(value) - 1 else ""
        rendered = format_initializer(item, indent + 1)
        lines.append(f"{child_pad}{append_initializer_suffix(rendered, suffix)}")
    lines.append(f"{pad}}}")
    return "\n".join(lines)


def compact_initializer(value: list[Any], indent: int) -> str | None:
    if has_commented_entry(value):
        return None

    if compact_wrapped_list(value):
        nested = init_raw_value(value[0])
        rendered = [format_initializer(item, indent) for item in nested]
        if all("\n" not in item for item in rendered):
            candidate = "{{ " + ", ".join(rendered) + " }}"
            if compact_initializer_fits(candidate, indent):
                return candidate

    if len(value) <= 16 and all(not isinstance(init_raw_value(item), list) for item in value):
        rendered = [format_initializer(item, indent) for item in value]
        if all("\n" not in item for item in rendered):
            candidate = "{ " + ", ".join(rendered) + " }"
            if compact_initializer_fits(candidate, indent):
                return candidate

    return None


def compact_initializer_fits(candidate: str, indent: int) -> bool:
    return len(("  " * indent) + candidate) <= COMPACT_INITIALIZER_LIMIT


def has_commented_entry(value: list[Any]) -> bool:
    return any(isinstance(item, InitEntry) and item.comment for item in value)


def compact_wrapped_list(value: list[Any]) -> bool:
    if len(value) != 1:
        return False
    nested = init_raw_value(value[0])
    return (
        isinstance(nested, list)
        and len(nested) <= 4
        and all(not isinstance(init_raw_value(item), list) for item in nested)
    )


def init_raw_value(value: Any) -> Any:
    return value.value if isinstance(value, InitEntry) else value


def append_initializer_comment(rendered: str, comment: str) -> str:
    if rendered.strip().endswith(f"/* {safe_comment(comment)} */"):
        return rendered
    return append_aligned_comment(rendered, f"/* {safe_comment(comment)} */", INITIALIZER_COMMENT_COLUMN)


def append_initializer_suffix(rendered: str, suffix: str) -> str:
    if not suffix:
        return rendered
    if "\n" in rendered:
        head, last = rendered.rsplit("\n", 1)
        return f"{head}\n{append_initializer_suffix(last, suffix)}"
    comment_match = re.match(r"^(?P<code>.*?)(?P<space>\s+)(?P<comment>/\* .+ \*/)$", rendered)
    if comment_match:
        code = f"{comment_match.group('code').rstrip()}{suffix}"
        return append_aligned_comment(code, comment_match.group("comment"), INITIALIZER_COMMENT_COLUMN)
    return f"{rendered}{suffix}"


def append_aligned_comment(rendered: str, comment: str, column: int) -> str:
    if "\n" in rendered:
        head, last = rendered.rsplit("\n", 1)
        return f"{head}\n{append_aligned_comment(last, comment, column)}"
    spaces = max(1, column - len(rendered))
    return f"{rendered}{' ' * spaces}{comment}"


def write_table_files(built: BuiltTable, output_dir: Path, force: bool) -> tuple[Path, Path]:
    basename = basename_for_table(built.table.name)
    h_path = output_dir / f"{basename}.h"
    c_path = output_dir / f"{basename}.c"
    if not force:
        for path in (h_path, c_path):
            if path.exists():
                raise FileExistsError(f"{path} already exists; pass --force to overwrite generated output")
    h_path.write_text(render_header(built), encoding="utf-8")
    c_path.write_text(render_source(built, h_path.name), encoding="utf-8")
    return c_path, h_path


def write_metadata_file(tables: list[DbtTable], output_dir: Path) -> Path:
    metadata = OrderedDict()
    for table in tables:
        metadata[table.name] = OrderedDict(
            [
                ("attrs", table.attrs),
                (
                    "blocks",
                    [
                        OrderedDict(
                            [
                                ("path", block.path),
                                ("quoted", block.quoted),
                                ("attrs", block.attrs),
                            ]
                        )
                        for block in table.blocks
                    ],
                ),
            ]
        )
    path = output_dir / "dbt_metadata.json"
    path.write_text(json.dumps(metadata, indent=2), encoding="utf-8")
    return path


def expected_output_paths(tables: list[DbtTable], output_dir: Path) -> set[Path]:
    expected: set[Path] = {output_dir / "dbt_metadata.json"}
    for table in tables:
        basename = basename_for_table(table.name)
        expected.add(output_dir / f"{basename}.c")
        expected.add(output_dir / f"{basename}.h")
    return expected


def unexpected_generated_files(output_dir: Path, expected: set[Path]) -> list[Path]:
    if not output_dir.exists():
        return []
    resolved_expected = {path.resolve() for path in expected}
    return [
        path
        for path in sorted(output_dir.glob("*"))
        if path.suffix.lower() in {".c", ".h", ".json"} and path.resolve() not in resolved_expected
    ]


def prune_unexpected_generated_files(output_dir: Path, expected: set[Path]) -> None:
    """Remove stale generated .c/.h/.json files from the output directory."""

    for path in unexpected_generated_files(output_dir, expected):
        path.unlink()


def settle_and_prune_generated_files(output_dir: Path, expected: set[Path]) -> None:
    for delay in (0.0, 0.5, 1.5, 3.0):
        if delay:
            time.sleep(delay)
        prune_unexpected_generated_files(output_dir, expected)


def print_table_list(tables: list[DbtTable], dbt_file: Path) -> None:
    print(f"{dbt_file}: {len(tables)} table(s)")
    for table in tables:
        description = normalize_comment_text(table.attrs.get("description", ""))
        if description:
            print(f"  {table.name}: {description}")
        else:
            print(f"  {table.name}")


def print_dry_run(tables: list[DbtTable], dbt_file: Path, output_dir: Path, clean: bool) -> None:
    expected = expected_output_paths(tables, output_dir)
    stale = unexpected_generated_files(output_dir, expected) if clean else []

    print(f"Input:  {dbt_file}")
    print(f"Output: {output_dir}")
    print(f"Would write {len(tables)} .c/.h table pair(s) and dbt_metadata.json")
    if clean:
        print(f"Would prune {len(stale)} stale generated file(s)")


def generate_output(
    dbt_file: Path,
    output_dir: Path,
    force: bool,
    clean: bool,
    tables: list[DbtTable] | None = None,
) -> tuple[int, Path]:
    if tables is None:
        tables = parse_dbt(dbt_file)
    if not tables:
        raise ValueError(f"No tables found in {dbt_file}")

    output_dir.mkdir(parents=True, exist_ok=True)

    expected = expected_output_paths(tables, output_dir)
    if clean:
        prune_unexpected_generated_files(output_dir, expected)

    written = []
    for table in tables:
        built = build_table(table)
        written.append(write_table_files(built, output_dir, force))
    metadata_path = write_metadata_file(tables, output_dir)

    if clean:
        settle_and_prune_generated_files(output_dir, expected)

    return len(written), metadata_path


def choose_dbt_file() -> Path | None:
    try:
        import tkinter as tk
        from tkinter import filedialog
    except ImportError as exc:
        print(f"Could not open a file picker: {exc}", file=sys.stderr)
        return None

    initial_dir = DEFAULT_DBT_FILE.parent if DEFAULT_DBT_FILE.parent.exists() else SCRIPT_DIR
    try:
        root = tk.Tk()
        root.withdraw()
        root.attributes("-topmost", True)
    except tk.TclError as exc:
        print(f"Could not open a file picker: {exc}", file=sys.stderr)
        return None

    selected = filedialog.askopenfilename(
        title="Choose the .dbt file to convert",
        initialdir=str(initial_dir),
        filetypes=[("DBT files", "*.dbt"), ("All files", "*.*")],
    )
    root.destroy()

    return Path(selected) if selected else None


def show_popup(title: str, message: str, error: bool = False) -> None:
    try:
        import tkinter as tk
        from tkinter import messagebox
    except ImportError:
        return

    try:
        root = tk.Tk()
        root.withdraw()
        root.attributes("-topmost", True)
    except tk.TclError:
        return
    if error:
        messagebox.showerror(title, message)
    else:
        messagebox.showinfo(title, message)
    root.destroy()


def open_output_folder(path: Path) -> None:
    try:
        if sys.platform == "darwin":
            subprocess.Popen(["open", str(path)])
        elif os.name == "nt":
            os.startfile(str(path))  # type: ignore[attr-defined]
        else:
            subprocess.Popen(["xdg-open", str(path)])
    except OSError as exc:
        print(f"Could not open output folder: {exc}", file=sys.stderr)


def run_file_picker_mode() -> int:
    dbt_file = choose_dbt_file()
    if dbt_file is None:
        print("No DBT file selected.")
        return 0

    if not dbt_file.is_file():
        message = f"That file could not be found:\n{dbt_file}"
        print(message, file=sys.stderr)
        show_popup("DBT file not found", message, error=True)
        return 1

    try:
        written_count, metadata_path = generate_output(
            dbt_file=dbt_file,
            output_dir=DEFAULT_OUTPUT_DIR,
            force=True,
            clean=True,
        )
    except Exception as exc:
        message = f"Could not generate tables:\n{exc}"
        print(message, file=sys.stderr)
        show_popup("Generation failed", message, error=True)
        return 1

    message = (
        f"Generated {written_count} table source/header pair(s).\n\n"
        f"Output folder:\n{DEFAULT_OUTPUT_DIR}\n\n"
        f"Metadata:\n{metadata_path}"
    )
    print(message)
    show_popup("Generation complete", message)
    open_output_folder(DEFAULT_OUTPUT_DIR)
    return 0


def main() -> int:
    if len(sys.argv) == 1:
        return run_file_picker_mode()

    parser = argparse.ArgumentParser(
        description="Generate .c/.h table files from a .dbt file.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=(
            "Examples:\n"
            "  python3 dbt_to_ch.py --clean --force\n"
            "  python3 dbt_to_ch.py --list-tables\n"
            "  python3 dbt_to_ch.py Tables/table_ACS.dbt -o generated_from_dbt --dry-run"
        ),
    )
    parser.add_argument(
        "dbt_file",
        nargs="?",
        type=Path,
        default=DEFAULT_DBT_FILE,
        help="Input DBT file.",
    )
    parser.add_argument("-o", "--output-dir", type=Path, default=DEFAULT_OUTPUT_DIR, help="Output directory.")
    parser.add_argument("--force", action="store_true", help="Overwrite files in the output directory.")
    parser.add_argument("--clean", action="store_true", help="Prune stale generated files before and after writing.")
    parser.add_argument("--dry-run", action="store_true", help="Show what would be written without changing files.")
    parser.add_argument("--list-tables", action="store_true", help="Print DBT table names and exit.")
    args = parser.parse_args()

    if not args.dbt_file.exists():
        parser.error(f"Input DBT file not found: {args.dbt_file}")
    if not args.dbt_file.is_file():
        parser.error(f"Input DBT path is not a file: {args.dbt_file}")

    tables = parse_dbt(args.dbt_file)
    if not tables:
        print(f"No tables found in {args.dbt_file}", file=sys.stderr)
        return 1

    if args.list_tables:
        print_table_list(tables, args.dbt_file)
        return 0

    if args.dry_run:
        print_dry_run(tables, args.dbt_file, args.output_dir, args.clean)
        return 0

    try:
        written_count, metadata_path = generate_output(
            dbt_file=args.dbt_file,
            output_dir=args.output_dir,
            force=args.force,
            clean=args.clean,
            tables=tables,
        )
    except FileExistsError as exc:
        print(f"Error: {exc}", file=sys.stderr)
        print("Tip: add --force when you mean to refresh generated output.", file=sys.stderr)
        return 2

    print(f"Generated {written_count} table source/header pair(s) in {args.output_dir}")
    print(f"Metadata written to {metadata_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
