# 04 — Voleta

*2021 · C · kernel + libc + cross-toolchain as siblings*

Named for *violette* — "violet" in French. Three co-equal trees instead
of kernel-with-toolchain-on-the-side.

- [kernel/](kernel/) — kernel sources with `arch/`, `include/`, and
  nested `kernel/`. See [kernel/README.md](kernel/README.md).
- [libc/](libc/) — custom libc (`voleta_libc/crt`, `voleta_libc/include`,
  `voleta_libc/libc`) plus kernel headers. See
  [libc/README.md](libc/README.md).
- [toolchain/](toolchain/) — naked GCC and Binutils cross-toolchain
  built from source for the `x86_64-voleta-elf` target. See
  [toolchain/README.md](toolchain/README.md).

Upstream repos originally lived as
`voleta-operating-system-kernel`, `voleta-custom-libc`, and
`voleta-naked-toolchain`. The Voleta toolchain is also what the
[03-astraea/](../03-astraea/) barebones kernel builds against.

Narrative context: see [../docs/lineage.md](../docs/lineage.md#voleta--getting-serious-about-toolchains).
