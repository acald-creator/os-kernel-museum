# 01 — KairosOS v1

*~2020 · C · first real kernel*

The first end-to-end kernel attempt: a C kernel with its own libc and a
userspace tree, built against an `x86_64-kairos-elf` cross-compiler.

Project contents live in [hobby-kairos-os/](hobby-kairos-os/), which has
its own [README.md](hobby-kairos-os/README.md) and `Makefile`:

- `kairos_kernel/` — kernel sources
- `kairos_libc/` — custom freestanding libc
- `kairos_userspace/` — early userspace experiments
- `kairos_build/` — build outputs (preserved for reference)

The original plan included a Lua userland and Awesome WM as the desktop.
That part did not happen. The kernel booted, basic syscalls worked, and
the libc linked — which was enough to teach what a libc actually needs.

Narrative context: see [../docs/lineage.md](../docs/lineage.md#kairosos--the-first-real-kernel).
