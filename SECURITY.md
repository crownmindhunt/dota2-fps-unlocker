# Security Policy

## Supported versions

| version | supported |
|---------|-----------|
| 1.2.x   | yes       |
| 1.1.x   | no        |

## Reporting a vulnerability

Open a private security advisory on GitHub or mail
`security@dota2-fps-unlocker.invalid` (PGP key in `docs/`).

Please include:

- affected commit hash
- Windows build (e.g. `10.0.22631`)
- Dota 2 client.dll build id (from `logs/fps_unlocker.log`)
- a minimal repro

## Scope

In scope: memory corruption in the signature scanner, arbitrary-file-write via
`config_loader`, privilege escalation through the process handle we open.

Out of scope: Valve Anti-Cheat detections (see below), anything requiring a
kernel driver, and reports about the tool being "detected". VAC bans are the
user's risk; the README says so clearly.

## Known risk surface

`ProcessAttach::by_name` opens `dota2.exe` with `PROCESS_ALL_ACCESS`. This is
intentional for `WriteProcessMemory` but means the optimizer runs with the
same privileges as the game. Do not run the unlocker as Administrator on a
shared machine.