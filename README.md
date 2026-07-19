# Phantom2

Red team implant with io_uring, encrypted C2, persistence, and keylogging capabilities.

## Description

Phantom2 is a stealthy implant written in C that utilizes io_uring for asynchronous I/O,
encrypted command and control (C2) communication, persistence mechanisms, and a keylogger.
It is intended for educational and authorized penetration testing purposes only.

## Features

- Asynchronous I/O using io_uring (no external liburing required)
- Encrypted C2 channel using XOR and a simplified ChaCha20-like stream cipher
- Persistence via systemd service and cron @reboot
- Keylogger (evdev-based) with enable/disable commands
- Screenshot capture (placeholder function)
- Self-destruct mechanism
- Anti-forensic measures (clearing history, setting process name, disabling core dumps)
- Configurable C2 server, port, and encryption key at compile time or via command line

## Compilation

The project can be compiled with the provided script or directly with gcc:

```sh
gcc -O2 -fPIC -o phantom phantom.c -ldl -pthread -lm
```

Alternatively, use the provided script:

```sh
./compile_run.sh
```

## Usage

After compiling, run the binary with optional arguments:

```sh
./phantom [--install] [--server SERVER_IP] [--port PORT]
```

- `--install`: Installs persistence (systemd service and cron job) and exits.
- `--server SERVER_IP`: Sets the C2 server address (default: 192.168.1.120).
- `--port PORT`: Sets the C2 server port (default: 4444).

Once running, the implant will beacon to the C2 server and await commands.

### C2 Commands (sent from the server)

The implant understands the following commands (sent as JSON-like structures via the C2 channel):

- `keylog_on`: Starts the keylogger.
- `keylog_off`: Stops the keylogger.
- `screenshot`: Takes a screenshot (saved to /tmp/screenshot_<PID>.png).
- `selfdestruct`: Removes persistence artifacts and deletes the binary.
- Other commands can be added by modifying the `process_command` function.

## Configuration

Default values are defined at the top of `phantom.c`:

- `DEFAULT_SERVER`: "192.168.1.120"
- `DEFAULT_PORT`: 4444
- `ENCRYPT_KEY`: "Ph4nt0m_2024_!@#$"
- `BEACON_INTERVAL`: 30 seconds
- `JITTER_PERCENT`: 30
- `IO_URING_QUEUE_DEPTH`: 64

These can be changed by editing the defines and recompiling, or overridden at runtime with `--server` and `--port`.

## Disclaimer

This software is for educational and authorized testing only. The author is not responsible for any misuse or damage caused by this program. Use only on systems you own or have explicit permission to test.

--
grisun0 of lazyown redteam