# 00 — Bootstrapping

Pre-kernel experiments: writing code with nothing underneath it.

Three separate projects in this era, each exploring how far down the
"nothing beneath you" stack you can go before you need someone else's
compiler.

- **[assembly-toy-language/](assembly-toy-language/)** — NASM and FASM
  examples, a `toy-program` target, and `bootstrap-from-assembly.sh`.
  Starting point for writing real programs in raw assembly.
- **[bcompiler/](bcompiler/)** — a staged bootstrap compiler
  (`hex1 → hex2a → hex3 → hex4 → hex5 → bcc`). Each stage is written in
  the previous stage's input format and adds one feature. The included
  [README](bcompiler/README) documents the full chain. i386-linux only.
- **[bootstrap-nani-compiler/](bootstrap-nani-compiler/)** — an
  exploration toward self-hosting: `assembly_sources/` and `c_sources/`
  plus `assembler/`, with `success/` and `failures/` directories that
  preserved what did and didn't work.

Narrative context: see [../docs/lineage.md](../docs/lineage.md#bootstrapping-from-nothing).
