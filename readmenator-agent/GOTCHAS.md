# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `phantom.c` (score: 4.00)
- `server.py` (score: 0.30)
- `compile_run.sh` (score: 0.00)

## Hotspots (complexity + centrality)

- `phantom.c` -- complexity: 1.0, centrality: 1.0, combined: 1.0
- `server.py` -- complexity: 0.1, centrality: 0.1, combined: 0.1
- `compile_run.sh` -- complexity: 0.0, centrality: 0.0, combined: 0.0

## Dataflow Issues (INFERRED, review each lead)

- `server.py:26` `main` [UNCHECKED_ALLOC] `s`: Result of allocator stored in `s` is never checked against NULL.
