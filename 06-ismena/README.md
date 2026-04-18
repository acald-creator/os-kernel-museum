# 06 — IsmenaOS

*2021 · C / ASM · Swift-runtime concept (on hold)*

A C/Assembly kernel designed to host a Swift runtime for userspace. The
kernel and libc shipped; the Swift runtime never did.

- [kernel/](kernel/) — kernel tree with `ismenaos-kernel/`,
  `ismenaos-libc/`, a placeholder `ismenaos-runtime/`, and
  `third-party/`. See [kernel/README.md](kernel/README.md).
- [libc/](libc/) — standalone custom libc with `crt/` and `libc/`
  subtrees. See [libc/README.md](libc/README.md).

Swift expects Darwin or Linux underneath it. The runtime support the
language assumes turned out to be far more than a hobby kernel can
reasonably provide. The honest README line from the original repo —
*"put on hold for further research"* — still applies.

Narrative context: see [../docs/lineage.md](../docs/lineage.md#ismenaos--the-swift-runtime-that-never-was).
