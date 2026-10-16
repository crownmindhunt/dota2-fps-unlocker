# Contributing to dota2-fps-unlocker

Thanks for helping keep the unlocker working across Dota 2 patches.

## Ground rules

- Every PR that touches `src/utils/memory_patch.cpp` or a signature in
  `src/core/optimizer_core.cpp` **must** include the client.dll build id you
  tested against. Signatures drift every major patch.
- Don't commit anything under `logs/`, `build/`, or your personal
  `config/user.toml`.
- New plugins go under `src/plugins/<name>/` and must ship a `plugin.json`
  with `name`, `version`, `target`, and `enabled`.

## Build

```
cmake -B build -A x64
cmake --build build --config Release
```

The binary expects to run as the same user that owns the Dota 2 process. We
do not support kernel drivers and won't merge PRs that add one.

## Style

- 4-space indent, no tabs.
- Prefer `std::wstring` for anything that ends up in a Win32 call.
- Log via `LogWriter`, never `std::wcout` from hot paths.

## Legal

This is a local performance tool. Do not use it to gain an in-game advantage,
do not submit PRs that add gameplay-automation features (auto-cast, last-hit
assist, movement prediction). Those get closed on sight.