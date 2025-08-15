# extract_c_tables_runbutton.py
# No external deps. Creates Excel-XML with one worksheet per *.h/*.c pair in this folder.
# Columns: Type, Field, Index, Value, Comment, Variant

import re
import platform
import subprocess
from pathlib import Path
from typing import List, Tuple, Dict, Any, Optional, Union

OUTPUT_FILENAME = "c_table_extract_pairs.xml"
SCRIPT_DIR = Path(__file__).resolve().parent

# ----------------- small utils -----------------
def read_text(p: Path) -> str:
    return p.read_text(errors="ignore")

def collapse_spaces(s: str) -> str:
    return re.sub(r"\s+", " ", s or "").strip()

def xml_escape(s: str) -> str:
    return (s or "").replace("&","&amp;").replace("<","&lt;").replace(">","&gt;").replace('"',"&quot;").replace("'","&apos;")

def sheet_name_safe(name: str) -> str:
    bad = set('[]:*?/\\')
    short = "".join(ch for ch in (name or "") if ch not in bad)[:31]
    return short or "Sheet"

def strip_comments_only(s: str) -> str:
    s = re.sub(r"/\*.*?\*/", "", s or "", flags=re.S)
    s = re.sub(r"//.*?$", "", s, flags=re.M)
    return s

def strip_all_comments_and_collapse(s: str) -> str:
    return collapse_spaces(strip_comments_only(s))

def _skip_comment(s: str, i: int) -> int:
    if s[i:i+2] == "/*":
        j = s.find("*/", i+2)
        return (j+2) if j != -1 else len(s)
    if s[i:i+2] == "//":
        j = s.find("\n", i+2)
        return (j+1) if j != -1 else len(s)
    return i

# ----------------- header (typedef/struct) -----------------
QUALIFIERS = {"const","volatile","static","extern","register","unsigned","signed","long","short"}

def find_typedef_struct_blocks(header_text: str) -> List[Tuple[str, str]]:
    pos = 0
    blocks: List[Tuple[str, str]] = []
    while True:
        m = re.search(r"typedef\s+struct\b", header_text[pos:])
        if not m: break
        start = pos + m.end()
        i = header_text.find("{", start)
        if i == -1: break
        depth = 0; j = i; n = len(header_text); end_brace = None
        while j < n:
            if header_text[j:j+2] in ("/*","//"):
                j = _skip_comment(header_text, j); continue
            ch = header_text[j]
            if ch == "{": depth += 1
            elif ch == "}":
                depth -= 1
                if depth == 0: end_brace = j; break
            j += 1
        if end_brace is None: break
        k = end_brace + 1
        while k < n and header_text[k].isspace(): k += 1
        l = header_text.find(";", k)
        if l == -1: break
        body = header_text[i+1:end_brace]
        names_str = header_text[k:l].strip()
        blocks.append((body, names_str))
        pos = l + 1
    return blocks

def split_names(names: str) -> List[str]:
    out = []
    for chunk in names.split(","):
        name = chunk.strip().lstrip("*").strip()
        name = re.split(r"\s+", name)[0] if name else ""
        if name: out.append(name)
    return out

def is_table_alias(name: str) -> bool:
    return bool(re.search(r"table.*_type$", name, flags=re.I))

def split_decls_at_depth_one(inner_text: str) -> List[str]:
    decls, cur, depth, i, n = [], [], 0, 0, len(inner_text or "")
    s = inner_text or ""
    while i < n:
        if s[i:i+2] in ("/*","//"):
            j = _skip_comment(s, i); cur.append(s[i:j]); i = j; continue
        ch = s[i]
        if ch == "{": depth += 1; cur.append(ch)
        elif ch == "}": depth = max(0, depth-1); cur.append(ch)
        elif ch == ";" and depth == 0:
            cur.append(ch); decls.append("".join(cur).strip()); cur = []
        else:
            cur.append(ch)
        i += 1
    if cur and "".join(cur).strip(): decls.append("".join(cur).strip())
    return decls

def extract_inner_of_nested_struct_decl(decl: str) -> Optional[str]:
    s = decl; i = s.find("{")
    if i == -1: return None
    depth, start, n = 0, None, len(s); j = i
    while j < n:
        if s[j:j+2] in ("/*","//"):
            k = _skip_comment(s, j); j = k; continue
        ch = s[j]
        if ch == "{":
            depth += 1
            if start is None: start = j
        elif ch == "}":
            depth -= 1
            if depth == 0 and start is not None:
                return s[start+1:j]
        j += 1
    return None

def parse_decl_type_name_index(decl_line: str) -> Tuple[str, str, str, bool, Optional[str]]:
    s_no = re.sub(r"/\*.*?\*/", "", decl_line, flags=re.S).strip()
    m_end = re.search(r"}\s*([A-Za-z_]\w*)\s*;\s*$", s_no, flags=re.S)
    if m_end:
        name = m_end.group(1)
        inner = extract_inner_of_nested_struct_decl(decl_line)
        return ("struct", name, "", True, inner)
    s = s_no
    if s.endswith(";"): s = s[:-1]
    s = re.sub(r"\([^)]*\)", "", s)
    s = re.sub(r"\s+", " ", s).strip()
    idx = ""
    m_br = re.search(r"(\s*(\[[^\]]*\]\s*)+)\s*$", s)
    if m_br:
        idx = re.sub(r"\s+", "", m_br.group(1))
        s = s[:m_br.start()].rstrip()
    tokens = s.split(" ")
    if not tokens: return ("", "", idx, False, None)
    name = tokens[-1]
    type_tokens = tokens[:-1]
    if name.startswith("*"):
        name = name.lstrip("*")
    base_type = " ".join(t for t in type_tokens if t and t not in QUALIFIERS).strip()
    return (base_type, name, idx, False, None)

def build_header_nodes(inner_text: str, typedef_nodes: Dict[str, List[Dict[str, Any]]]) -> List[Dict[str, Any]]:
    nodes: List[Dict[str, Any]] = []
    for d in split_decls_at_depth_one(inner_text or ""):
        t, n, idx, is_nested, inner = parse_decl_type_name_index(d)
        if is_nested and inner is not None:
            nodes.append({'kind':'struct', 'Name': n, 'Children': build_header_nodes(inner, typedef_nodes)})
        elif n:
            if t in typedef_nodes:
                nodes.append({'kind':'struct_typedef', 'Type': t, 'Field': n, 'Index': idx, 'Children': typedef_nodes[t]})
            else:
                nodes.append({'kind':'simple', 'Type': t, 'Field': n, 'Index': idx})
    return nodes

def build_header_nodes_tree(header_text: str):
    blocks = find_typedef_struct_blocks(header_text)
    typedef_nodes: Dict[str, List[Dict[str, Any]]] = {}
    table_aliases: List[Tuple[str, str]] = []
    all_names_bodies: List[Tuple[str, str]] = []
    for body, names_str in blocks:
        for name in split_names(names_str):
            all_names_bodies.append((name, body))
            if is_table_alias(name):
                table_aliases.append((name, body))
    for name, _ in all_names_bodies: typedef_nodes[name] = []
    for name, body in all_names_bodies:
        typedef_nodes[name] = build_header_nodes(body, typedef_nodes)
    return typedef_nodes, table_aliases

# ----------------- preprocessor: export all SV_ID branches -----------------
_directive_re = re.compile(r"^\s*#\s*(if|elif|else|endif)\b", re.I)
_sv_branch_pat = re.compile(r"#\s*(if|elif)\s*\(\s*SV_ID\s*==\s*(\d+)\s*\)", re.I)

def collect_sv_variants(s: str) -> List[str]:
    found = _sv_branch_pat.findall(s or "")
    vals = sorted({n for (_k, n) in found}, key=lambda x: int(x))
    return (vals + ["ELSE"]) if vals else [None]

def eval_expr_sv(expr: str, sv_value: Optional[str], force_else: bool=False) -> Optional[bool]:
    if sv_value is None: return None
    m = re.search(r"SV_ID\s*==\s*(\d+)", expr or "")
    if not m: return False if force_else else None
    return (m.group(1) == sv_value) if not force_else else False

def resolve_conditionals_for_variant(text: str, sv_value: Optional[str]) -> str:
    if not text: return ""
    lines = text.splitlines(True)
    i, n = 0, len(lines)
    out: List[str] = []

    def parse_if_group(start_idx: int) -> Tuple[str, int]:
        i = start_idx
        assert _directive_re.match(lines[i]).group(1).lower() == "if"
        i += 1
        branches: List[Tuple[str, List[str]]] = []
        cur_cond = lines[start_idx].strip()
        cur_buf: List[str] = []
        while i < n:
            dm = _directive_re.match(lines[i])
            if dm and dm.group(1).lower() == "if":
                nested, i2 = parse_if_group(i); cur_buf.append(nested); i = i2; continue
            if dm and dm.group(1).lower() == "elif":
                branches.append((cur_cond, cur_buf)); cur_buf = []; cur_cond = lines[i].strip(); i += 1; continue
            if dm and dm.group(1).lower() == "else":
                branches.append((cur_cond, cur_buf)); cur_buf = []; cur_cond = "ELSE"; i += 1; continue
            if dm and dm.group(1).lower() == "endif":
                branches.append((cur_cond, cur_buf)); i += 1; break
            cur_buf.append(lines[i]); i += 1

        chosen_buf: List[str] = []
        matched = False
        if sv_value is None:
            chosen_buf = branches[-1][1]
        else:
            force_else = (sv_value == "ELSE")
            for cond, buf in branches:
                if cond == "ELSE":
                    else_buf = buf
                    if force_else: chosen_buf = else_buf; matched = True; break
                    continue
                expr = re.sub(r"^\s*#\s*(if|elif)\s*", "", cond or "", flags=re.I)
                if eval_expr_sv(expr, sv_value):
                    chosen_buf = buf; matched = True; break
            if not matched:
                for cond, buf in branches:
                    if cond == "ELSE":
                        chosen_buf = buf; break

        return resolve_conditionals_for_variant("".join(chosen_buf), sv_value), i

    while i < n:
        dm = _directive_re.match(lines[i])
        if dm and dm.group(1).lower() == "if":
            chosen, i = parse_if_group(i); out.append(chosen)
        else:
            if not dm: out.append(lines[i])
            i += 1
    return "".join(out)

# ----------------- value parsing helpers (keep comments) -----------------
def inner_of_braced_value_keep_comments(s: str) -> Optional[str]:
    if not s: return None
    s = s.strip()
    if not s.startswith("{"): return None
    depth = 0; started = False; out: List[str] = []; i = 0; n = len(s)
    while i < n:
        if s[i:i+2] == "/*":
            j = s.find("*/", i+2); j = (n-2) if j == -1 else j
            if started and depth >= 1: out.append(s[i:j+2])
            i = j + 2; continue
        if s[i:i+2] == "//":
            j = s.find("\n", i+2); j = n if j == -1 else j
            if started and depth >= 1: out.append(s[i:j])
            i = j; continue
        ch = s[i]
        if ch == "{":
            depth += 1
            if not started: started = True
            else: out.append(ch)
        elif ch == "}":
            depth -= 1
            if depth >= 1: out.append(ch)
            else: return "".join(out)
        else:
            if started and depth >= 1: out.append(ch)
        i += 1
    return "".join(out) if out else None

def split_top_level_items_with_cmts(s: str) -> List[Tuple[str, str]]:
    """Return [(core_item_text, trailing_or_attached_comment_text)] at top level (keeps comments)."""
    if not s: return []
    text = s.strip()
    if text.startswith("{") and text.endswith("}"):
        inner = inner_of_braced_value_keep_comments(text)
        if inner is None: inner = text[1:-1]
        text = inner

    items: List[Tuple[str, str]] = []
    i, n = 0, len(text)
    cur: List[str] = []
    depth = 0
    post_cmts_for_current: List[str] = []
    pre_cmts_for_next: List[str] = []
    started_this_item = False

    def take_line_comment(pos: int) -> Tuple[str, int]:
        j = text.find("\n", pos+2); j = n if j == -1 else j
        return collapse_spaces(text[pos+2:j]), j

    def take_block_comment(pos: int) -> Tuple[str, int]:
        j = text.find("*/", pos+2); j = n-2 if j == -1 else j
        return collapse_spaces(text[pos+2:j]), j+2

    def finalize_current():
        nonlocal cur, post_cmts_for_current, started_this_item
        core = "".join(cur).strip()
        cmt = " ".join(post_cmts_for_current).strip()
        if core or cmt: items.append((core, cmt))
        cur = []; post_cmts_for_current = []; started_this_item = False

    while i < n:
        if text[i].isspace():
            cur.append(text[i]); i += 1; continue

        if text[i:i+2] == "/*" and depth == 0:
            c, i = take_block_comment(i)
            if started_this_item or cur: post_cmts_for_current.append(c)
            else: pre_cmts_for_next.append(c)
            continue
        if text[i:i+2] == "//" and depth == 0:
            c, i = take_line_comment(i)
            if started_this_item or cur: post_cmts_for_current.append(c)
            else: pre_cmts_for_next.append(c)
            continue

        if text[i:i+2] == "/*":
            c, i2 = take_block_comment(i); cur.append("/*"+c+"*/"); i = i2; continue
        if text[i:i+2] == "//":
            c, i2 = take_line_comment(i); cur.append("//"+c); i = i2; continue

        ch = text[i]
        if ch == "{":
            if not started_this_item:
                if pre_cmts_for_next:
                    post_cmts_for_current.extend(pre_cmts_for_next); pre_cmts_for_next = []
                started_this_item = True
            depth += 1; cur.append(ch); i += 1; continue
        if ch == "}":
            depth -= 1; cur.append(ch); i += 1; continue

        if ch == "," and depth == 0:
            i += 1
            # collect comments that immediately follow the comma
            while i < n:
                while i < n and text[i].isspace(): i += 1
                if text[i:i+2] == "/*":
                    c, i = take_block_comment(i); post_cmts_for_current.append(c); continue
                if text[i:i+2] == "//":
                    c, i = take_line_comment(i); post_cmts_for_current.append(c); continue
                break
            finalize_current()
            continue

        if depth == 0 and not started_this_item:
            if pre_cmts_for_next:
                post_cmts_for_current.extend(pre_cmts_for_next); pre_cmts_for_next = []
            started_this_item = True

        cur.append(ch); i += 1

    finalize_current()
    return items

# ----------------- value tree + splitting -----------------
def inner_of_braced_value(s: str) -> Optional[str]:
    if not s: return None
    s = s.strip()
    if not s.startswith("{"): return None
    depth = 0; start = None; i = 0; n = len(s)
    while i < n:
        if s[i:i+2] in ("/*","//"):
            j = _skip_comment(s, i); i = j; continue
        ch = s[i]
        if ch == "{":
            depth += 1
            if start is None: start = i
        elif ch == "}":
            depth -= 1
            if depth == 0 and start is not None:
                return s[start+1:i]
        i += 1
    return None

def split_items_core_only(inner: str) -> List[str]:
    items: List[str] = []
    i, n = 0, len(inner or "")
    while i < n:
        while i < n and inner[i].isspace(): i += 1
        if i >= n: break
        cur = []; depth = 0
        while i < n:
            if inner[i:i+2] in ("/*","//"):
                j = _skip_comment(inner, i); i = j; continue
            ch = inner[i]
            if ch == "{": depth += 1; cur.append(ch)
            elif ch == "}": depth -= 1; cur.append(ch)
            elif ch == "," and depth == 0: i += 1; break
            else: cur.append(ch)
            i += 1
        item_text = "".join(cur).strip()
        if item_text: items.append(item_text)
    return items

def map_nodes_to_items_min(nodes: List[Dict[str, Any]], items: List[str]) -> Tuple[List[List[str]], List[str]]:
    rows: List[List[str]] = []
    remaining = list(items)
    for node in nodes:
        kind = node['kind']
        if kind == 'simple':
            item_text = remaining.pop(0) if remaining else ""
            rows.append([node["Type"], node["Field"], node["Index"], strip_all_comments_and_collapse(item_text)])
        elif kind in ('struct', 'struct_typedef'):
            block_text = remaining.pop(0) if remaining else "{}"
            inner = inner_of_braced_value(block_text) or ""
            subitems = split_items_core_only(inner)
            sub_rows, _ = map_nodes_to_items_min(node["Children"], subitems)
            rows.extend(sub_rows)
    return rows, remaining

# ----------------- COMMENT MAP (improved & deeper) -----------------
_index_part_re = re.compile(r"\[([^\]]*)\]")

def parse_index_parts(index_str: str) -> List[str]:
    return _index_part_re.findall(index_str or "")

def explode_index_and_value(index_str: str, value_text: str) -> List[Tuple[str, str]]:
    parts = parse_index_parts(index_str)
    if not parts or not value_text.strip():
        return [(index_str, strip_all_comments_and_collapse(value_text))]
    # Build a generic tree (values only) to count children; then 1-based indices
    def parse_generic(val: str) -> Union[str, List[Any]]:
        val = val.strip()
        if not val.startswith("{"):
            return strip_all_comments_and_collapse(val)
        inner = inner_of_braced_value(val) or ""
        items = split_items_core_only(inner)
        out=[]
        for it in items:
            out.append(parse_generic(it))
        return out
    def stringify(node):
        if isinstance(node, str): return node
        return "{ " + ", ".join(stringify(ch) for ch in node) + " }"
    tree = parse_generic(value_text)
    results: List[Tuple[str, str]] = []
    def walk(node, level, idx_prefix):
        if level == len(parts):
            results.append(("".join(f"[{i}]" for i in idx_prefix), stringify(node)))
            return
        if isinstance(node, list) and node:
            for i, ch in enumerate(node, start=1):
                walk(ch, level+1, idx_prefix+[i])
        else:
            results.append(("".join(f"[{i}]" for i in idx_prefix+[1]), stringify(node)))
    walk(tree, 0, [])
    return results

def collect_indexed_comments(value_text: str, depth_limit: int = 6) -> Dict[Tuple[int, ...], str]:
    """
    Recursively collect comments for items at any nesting depth.
    Returns map: (i,) or (i,j) or (i,j,k) ... -> "comment text"
    """
    value_text = value_text.strip()
    out: Dict[Tuple[int, ...], str] = {}

    def rec(block: str, prefix: Tuple[int, ...], depth: int):
        if depth > depth_limit: return
        pairs = split_top_level_items_with_cmts(block)
        for i, (core, cmt) in enumerate(pairs, start=1):
            if cmt:
                out[prefix + (i,)] = cmt
            core_s = core.strip()
            if core_s.startswith("{"):
                inner = inner_of_braced_value_keep_comments(core_s) or ""
                if inner:
                    rec(inner, prefix + (i,), depth+1)

    # If it's a simple scalar, there are no indices to collect
    if not value_text.startswith("{"):
        return out
    inner0 = inner_of_braced_value_keep_comments(value_text)
    if inner0 is None:
        return out
    rec(inner0, tuple(), 1)
    return out

def comment_map_for_nodes(nodes: List[Dict[str, Any]], inner_text_with_comments: str) -> Dict[Tuple[str, str], str]:
    """
    Build {(Field, Index or prefix)} -> comment
    - exact matches for [i], [i][j], [i][j][k]...
    - prefix fallback: [i] applies to [i][*]
    - field-level default via (Field, "*") from a header/pre-item comment
    """
    cmap: Dict[Tuple[str,str], str] = {}

    # Step 1: split the struct initializer into items (keep comments)
    top_pairs = split_top_level_items_with_cmts(inner_text_with_comments)

    def walk(nodes_local: List[Dict[str, Any]], pairs_local: List[Tuple[str,str]]):
        idx_pair = 0
        for node in nodes_local:
            kind = node['kind']
            if idx_pair >= len(pairs_local):
                # out of items; nothing to map
                continue
            core, top_cmt = pairs_local[idx_pair]
            idx_pair += 1

            if kind == 'simple':
                idx_decl = node["Index"]
                # Field-level default comment if provided before/at this item
                if top_cmt:
                    cmap[(node["Field"], "*")] = top_cmt

                # Per-element comments (any depth)
                if idx_decl and core.strip().startswith("{"):
                    per_map = collect_indexed_comments(core)
                    # store exact keys
                    for idx_tuple, cmt in per_map.items():
                        key = "".join(f"[{k}]" for k in idx_tuple)
                        cmap[(node["Field"], key)] = cmt

                else:
                    # scalar comment sits at this top-level item
                    if top_cmt:
                        cmap[(node["Field"], "")] = top_cmt

            elif kind in ('struct','struct_typedef'):
                # Dive into the nested block
                inner = inner_of_braced_value_keep_comments(core) or ""
                sub_pairs = split_top_level_items_with_cmts(inner)
                walk(node["Children"], sub_pairs)

    walk(nodes, top_pairs)
    return cmap

# ----------------- pair processing -----------------
def find_alias_initializers(ctxt: str, alias: str) -> List[str]:
    inners=[]
    for m in re.finditer(r"\b"+re.escape(alias)+r"\s+[A-Za-z_]\w*\s*=\s*{", ctxt, flags=re.S):
        start = m.end() - 1
        depth = 0; i = start; n = len(ctxt); inner = None
        while i < n:
            if ctxt[i:i+2] in ("/*","//"):
                j = _skip_comment(ctxt, i); i = j; continue
            ch = ctxt[i]
            if ch == '{': depth += 1
            elif ch == '}':
                depth -= 1
                if depth == 0: inner = ctxt[start+1:i]; break
            i += 1
        if inner is not None: inners.append(inner)
    return inners

def split_items_core_at_top(inner_text: str) -> List[str]:
    items=[]
    i, n = 0, len(inner_text or "")
    while i < n:
        while i < n and inner_text[i].isspace(): i += 1
        if i >= n: break
        cur = []; depth = 0
        while i < n:
            if inner_text[i:i+2] in ("/*","//"):
                j = _skip_comment(inner_text, i); i = j; continue
            ch = inner_text[i]
            if ch == "{": depth += 1; cur.append(ch)
            elif ch == "}": depth -= 1; cur.append(ch)
            elif ch == "," and depth == 0: i += 1; break
            else: cur.append(ch)
            i += 1
        item = "".join(cur).strip()
        if item: items.append(item)
    return items

def process_pair_to_rows_all_variants(h_path: Path, c_path: Path) -> List[List[str]]:
    htxt = read_text(h_path)
    ctxt = read_text(c_path)
    typedef_nodes, table_aliases = build_header_nodes_tree(htxt)
    out_rows: List[List[str]] = []

    for alias, body in table_aliases:
        nodes = typedef_nodes.get(alias, build_header_nodes(body, typedef_nodes))
        inits = find_alias_initializers(ctxt, alias)
        for inner in inits:
            variants = collect_sv_variants(inner)
            for sv in variants:
                inner_resolved = resolve_conditionals_for_variant(inner, sv)
                # values (without comments)
                core_items = split_items_core_at_top(inner_resolved)
                flat_rows, _ = map_nodes_to_items_min(nodes, core_items)
                # expand indices into separate rows
                expanded: List[List[str]] = []
                for Type, Field, Index, Value in flat_rows:
                    if Index and Value.strip().startswith("{"):
                        for idx_path, v in explode_index_and_value(Index, Value):
                            expanded.append([Type, Field, idx_path, v])
                    else:
                        expanded.append([Type, Field, Index, Value])

                # build comment map and attach
                c_map = comment_map_for_nodes(nodes, "{"+inner_resolved+"}")
                variant_label = f"SV_ID={sv}" if sv is not None else ""
                for Type, Field, Index, Value in expanded:
                    # exact match
                    cmt = c_map.get((Field, Index), "")
                    # if multi-dim and empty, try prefix [i]
                    if not cmt and Index:
                        m = re.match(r"(\[\d+\])(\[.*\])?", Index)
                        if m:
                            cmt = c_map.get((Field, m.group(1)), "") or cmt
                    # fall back to field-level default
                    if not cmt:
                        cmt = c_map.get((Field, "*"), "")
                    out_rows.append([Type, Field, Index, Value, cmt, variant_label])

    return out_rows

# ----------------- workbook XML -----------------
def make_workbook_xml(sheet_dict: Dict[str, List[List[str]]]) -> str:
    header = """<?xml version="1.0"?>
<?mso-application progid="Excel.Sheet"?>
<Workbook xmlns="urn:schemas-microsoft-com:office:spreadsheet"
 xmlns:o="urn:schemas-microsoft-com:office:office"
 xmlns:x="urn:schemas-microsoft-com:office:excel"
 xmlns:ss="urn:schemas-microsoft-com:office:spreadsheet"
 xmlns:html="http://www.w3.org/TR/REC-html40">
 <Styles>
  <Style ss:ID="Default" ss:Name="Normal">
   <Alignment ss:Vertical="Bottom"/>
   <Borders/><Font/><Interior/><NumberFormat/><Protection/>
  </Style>
  <Style ss:ID="sBold"><Font ss:Bold="1"/></Style>
 </Styles>
"""
    pieces = [header]
    for raw_name, rows in sheet_dict.items():
        name = sheet_name_safe(raw_name)
        pieces.append(f' <Worksheet ss:Name="{xml_escape(name)}">\n  <Table>\n')
        cols = ["Type","Field","Index","Value","Comment","Variant"]
        pieces.append("   <Row>")
        for c in cols:
            pieces.append(f'<Cell ss:StyleID="sBold"><Data ss:Type="String">{xml_escape(c)}</Data></Cell>')
        pieces.append("</Row>\n")
        for r in rows:
            pieces.append("   <Row>")
            for cell in r:
                pieces.append(f'<Cell><Data ss:Type="String">{xml_escape(cell)}</Data></Cell>')
            pieces.append("</Row>\n")
        pieces.append("  </Table>\n </Worksheet>\n")
    pieces.append("</Workbook>\n")
    return "".join(pieces)

# ----------------- discover pairs + run -----------------
def discover_pairs_by_stem(folder: Path) -> List[Tuple[Path, Path]]:
    hs = {p.stem: p for p in folder.glob("*.h")}
    cs = {p.stem: p for p in folder.glob("*.c")}
    return [(hs[s], cs[s]) for s in hs if s in cs]

def main():
    folder = SCRIPT_DIR
    pairs = discover_pairs_by_stem(folder)
    if not pairs:
        print("No matching *.h/*.c pairs in", folder); return

    sheets: Dict[str, List[List[str]]] = {}
    for h, c in pairs:
        rows = process_pair_to_rows_all_variants(h, c)
        sheets[h.stem] = rows

    xml = make_workbook_xml(sheets)
    out_path = folder / OUTPUT_FILENAME
    out_path.write_text(xml, encoding="utf-8")
    print(f"Wrote: {out_path}")
    try:
        if platform.system() == "Darwin":
            subprocess.run(["open", str(out_path)], check=False)
        elif platform.system() == "Windows":
            import os; os.startfile(str(out_path))  # type: ignore
    except Exception:
        pass

if __name__ == "__main__":
    main()