# OS Kernel Museum

> Four kernels later — the journey from hex bootstrapping to TerranoxOS.

A preserved lineage of hobby operating system kernels written between ~2020
and the present. Each directory holds an earlier project roughly as it was
left, alongside the lessons that carried forward into the next one.

This is not a tutorial. It's a museum: code kept in its original shape so
the progression — from raw hex bytes to a C kernel with a cross-compiled
libc, through a D-language exokernel experiment, to a pure-assembly
barebones kernel — stays legible.

Narrative context for each kernel — what it was, what it taught, what
carried forward — lives in [docs/lineage.md](docs/lineage.md).

## Timeline

| Era | Directory | Language | Focus |
|---|---|---|---|
| ~2020 | [00-bootstrapping/](00-bootstrapping/) | Hex / ASM | Hex → NASM → tiny ELF bootstrap chain (`bcompiler`, `nani`) |
| ~2020 | [01-kairos-v1/](01-kairos-v1/) | C | First real kernel: `kairos_kernel` + `kairos_libc` + `kairos_userspace` |
| ~2020 | [02-kairos-v2/](02-kairos-v2/) | C | Refined build (Jamroot), docs, LLVM/Clang attempt |
| 2022 | [03-astraea/](03-astraea/) | C / ASM | OSDev-style barebones kernel (`boot.s` + `kernel.c`) |
| 2021 | [04-voleta/](04-voleta/) | C | Kernel, custom libc, and naked GCC/Binutils cross-toolchain |
| 2021 | [05-exokernel-d/](05-exokernel-d/) | D | Exokernel architecture experiment in D |
| 2021 | [06-ismena/](06-ismena/) | C / ASM | IsmenaOS kernel + libc (Swift-runtime concept, shelved) |

## What lives in each directory

- **00-bootstrapping** — `assembly-toy-language/` (NASM/FASM examples),
  `bcompiler/` (the `hex1 → hex2 → … → bcc` staged bootstrap compiler),
  and `bootstrap-nani-compiler/` (assembly/C sources exploring
  self-hosting).
- **01-kairos-v1** — `hobby-kairos-os/` with kernel, libc, userspace, and
  a top-level Makefile. The first end-to-end attempt.
- **02-kairos-v2** — rebuild of KairosOS around a `Jamroot.jam` build, a
  cleaner `kernel/` + `libc/` split, and a `docs/` tree.
- **03-astraea** — a single-directory barebones kernel (`boot.s`,
  `kernel.c`, `linker.ld`) built against the Voleta cross-toolchain.
- **04-voleta** — three sibling trees: `kernel/`, `libc/`, and
  `toolchain/`. The toolchain is a first-class component here, not a
  dependency.
- **05-exokernel-d** — `barebones/` kernel written in D (`kernel.main.d`,
  `start.s`, `linker.ld`). A short-lived detour into D's metaprogramming.
- **06-ismena** — `kernel/` (with an `ismenaos-runtime/` placeholder for
  the Swift runtime that never shipped) and `libc/` (`crt/` + `libc/`).

## Building and booting

Each kernel has its own build story. The Voleta toolchain
(`i386-voletaos-elf-*` / `x86_64-voleta-elf-*`) is the common thread for
the later C kernels — see each subdirectory's `README.md` and `Makefile`
for specifics. Where a kernel boots under QEMU, the invocation lives
alongside its build instructions (for example,
[03-astraea/README.md](03-astraea/README.md)).

## Status

These projects are historical. None of them run a useful userland; all of
them taught something that shaped the next one. Active kernel work
(TerranoxOS) lives outside this repo.

## License

Licensing is per-subproject. Directories that ship a `LICENSE` file
(`03-astraea`, `04-voleta/*`, `05-exokernel-d`, `06-ismena/*`) are
governed by that file. Older directories without a license are preserved
as-is for historical reference.
