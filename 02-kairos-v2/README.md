# 02 — KairosOS v2

*~2020 · C · rebuild with better tooling*

The second pass at KairosOS: same goals as v1, cleaner layering, and a
`Jamroot` build at the top of the tree instead of a hand-rolled
Makefile. Also the point where an LLVM/Clang toolchain was attempted
alongside the GNU one.

Layout:

- [Jamroot.jam](Jamroot.jam) — top-level Boost.Build configuration
- [kernel/](kernel/) — kernel sources (`arch/`, `core/`, `modules/`,
  Limine/stivale2 boot glue)
- [libc/](libc/) — custom libc with `crt/`, `include/`, `src/`, and its
  own Jamfile
- [docs/](docs/) — build notes: compiling the GNU toolchain, compiling
  Clang, Kairos build instructions, and a setup script

v2 never reached a desktop either. What it did teach was that a build
system you don't fully understand costs more than the one you wrote
yourself — Jamroot was the wrong abstraction at the wrong time.

Narrative context: see [../docs/lineage.md](../docs/lineage.md#kairosos--the-first-real-kernel).
