# root

*Community 0 | 3 files | cohesion 1.00*

## Definition

This community groups 3 file(s) rooted at `root` with dominant language sh (cohesion 1.00). Central symbols: `BEACON_INTERVAL`, `CMD_BUFFER_SIZE`, `DEFAULT_PORT`, `DEFAULT_SERVER`, `ENCRYPT_KEY`, `IO_URING_QUEUE_DEPTH`, `JITTER_PERCENT`, `MAX_PATH`. Core file: `phantom.c` (40 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `compile_run.sh` | sh | utility | 0 | no |
| `phantom.c` | c | utility | 40 | no |
| `server.py` | py | utility | 3 | no |

## Key Symbols

- `_GNU_SOURCE` (macro, `phantom.c:7`) `#define _GNU_SOURCE`
- `DEFAULT_SERVER` (macro, `phantom.c:42`) `#define DEFAULT_SERVER`
- `DEFAULT_PORT` (macro, `phantom.c:43`) `#define DEFAULT_PORT`
- `ENCRYPT_KEY` (macro, `phantom.c:44`) `#define ENCRYPT_KEY`
- `BEACON_INTERVAL` (macro, `phantom.c:45`) `#define BEACON_INTERVAL`
- `JITTER_PERCENT` (macro, `phantom.c:46`) `#define JITTER_PERCENT`
- `IO_URING_QUEUE_DEPTH` (macro, `phantom.c:47`) `#define IO_URING_QUEUE_DEPTH`
- `CMD_BUFFER_SIZE` (macro, `phantom.c:48`) `#define CMD_BUFFER_SIZE`
- `MAX_PATH` (macro, `phantom.c:49`) `#define MAX_PATH`
- `io_uring_sq` (struct, `phantom.c:54`) - --------------------------------------------------------------------- IO_URING MANUAL (sin liburing)
- `io_uring_cq` (struct, `phantom.c:58`)
- `io_uring` (struct, `phantom.c:62`)
- `__io_uring_setup` (function, `phantom.c:69`) `static inline int __io_uring_setup(unsigned int entries, struct io_uring_params`
- `__io_uring_enter` (function, `phantom.c:72`) `static inline int __io_uring_enter(int fd, unsigned int to_submit, unsigned int`
- `__io_uring_register` (function, `phantom.c:76`) `static inline int __io_uring_register(int fd, unsigned int opcode, const void *a`
- `uring_queue_init` (function, `phantom.c:80`) `static int uring_queue_init(unsigned int entries, struct io_uring *ring)`
- `uring_get_sqe` (function, `phantom.c:120`) `static struct io_uring_sqe *uring_get_sqe(struct io_uring *ring)`
- `uring_submit` (function, `phantom.c:128`) `static int uring_submit(struct io_uring *ring)`
- `uring_wait_cqe_timeout` (function, `phantom.c:134`) `static int uring_wait_cqe_timeout(struct io_uring *ring, struct io_uring_cqe **c`
- `uring_cqe_seen` (function, `phantom.c:143`) `static inline void uring_cqe_seen(struct io_uring *ring, struct io_uring_cqe *cq`
- `chacha20_keystream` (function, `phantom.c:155`) `static void chacha20_keystream(uint32_t counter, uint8_t *key, uint8_t *nonce, u`
- `encrypt_payload` (function, `phantom.c:161`) `static void encrypt_payload(uint8_t *data, size_t len, uint8_t *key, uint8_t *no`
- `c2_command_t` (struct, `phantom.c:171`) - --------------------------------------------------------------------- ESTRUCTURA DE COMANDOS C2 ----
- `c2_response_t` (struct, `phantom.c:177`)
- `uring_read` (function, `phantom.c:221`) `static ssize_t uring_read(int fd, void *buf, size_t count, off_t offset)`
- `uring_write` (function, `phantom.c:243`) `static ssize_t uring_write(int fd, const void *buf, size_t count, off_t offset)`
- `run_shell_command` (function, `phantom.c:268`) `static char *run_shell_command(const char *cmd)` - --------------------------------------------------------------------- EJECUCIÓN DE COMANDOS --------
- `upload_file` (function, `phantom.c:303`) `static int upload_file(const char *local_path, const char *remote_path)` - --------------------------------------------------------------------- SUBIR / BAJAR ARCHIVOS -------
- `download_file` (function, `phantom.c:319`) `static int download_file(const char *remote_path, const char *local_path)`
- `install_persistence` (function, `phantom.c:326`) `static void install_persistence(void)` - --------------------------------------------------------------------- PERSISTENCIA -----------------

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 0
- Cross-boundary resolved imports (EXTRACTED): 0

## Connections

- No cross-community bridges recorded. This community is self-contained.

## Risks

- [taint medium] `phantom.c` -> `phantom.c` via `input` (0 hops)
- [dataflow UNCHECKED_ALLOC] `server.py:26` `main` `s`: Result of allocator stored in `s` is never checked against NULL.

## Open Questions

- Why do 3 file(s) lack file-level docs (e.g. `compile_run.sh`)? What purpose do they serve?
- Is the dangerous import `input` in `phantom.c` still required, or can it be isolated?
- What would break if the most connected file in root changed?
- Should root be split, given cohesion 1.00?

## Sources

- `compile_run.sh`
- `phantom.c`
- `server.py`
