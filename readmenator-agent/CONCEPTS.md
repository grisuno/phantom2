# Concepts

Nouns map atomically to file sets (EXTRACTED); verbs aggregate structural edges (INFERRED).

- `recv` | files=2 | mentions=3 | `phantom.c`, `server.py`
- `run` | files=2 | mentions=3 | `compile_run.sh`, `phantom.c`
- `server` | files=2 | mentions=3 | `phantom.c`, `server.py`

## Dialectic

- Thesis: `recv` centralizes 2 files; Antithesis: `server` pulls 2 files with 2 shared (Jaccard 1.00); Synthesis: should they merge, split by layer, or keep `bridges` explicit?
