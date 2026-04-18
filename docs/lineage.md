# The Kernel Lineage

Notes on each kernel in the museum: what it was, what worked, what didn't,
and what carried forward into the next one.

These are preserved as historical context, not as documentation of the
code. Each kernel's source lives in its own top-level directory.

---

## Timeline

| Era | Kernel | Language | Key idea | Directory |
|---|---|---|---|---|
| ~2020 | Assembly experiments | Hex / ASM | Hex bootstrapping, bare metal | [00-bootstrapping/](../00-bootstrapping/) |
| ~2020 | KairosOS v1 | C | First real kernel + libc + userspace | [01-kairos-v1/](../01-kairos-v1/) |
| ~2020 | KairosOS v2 | C | Refined build, docs, GNU/LLVM toolchain | [02-kairos-v2/](../02-kairos-v2/) |
| 2021 | Voleta | C | Custom libc, GCC/Binutils cross-toolchain | [04-voleta/](../04-voleta/) |
| 2021 | D Exokernel | D | Exokernel architecture experiment | [05-exokernel-d/](../05-exokernel-d/) |
| 2021 | IsmenaOS | C / ASM | Swift-runtime concept, custom libc | [06-ismena/](../06-ismena/) |
| 2022 | AstraeaOS | C / ASM | OSDev-style barebones kernel | [03-astraea/](../03-astraea/) |
| Current | TerranoxOS | C / ASM | 91-syscall ABI, capability tokens, ELF loader | *(outside this repo)* |

---

## Bootstrapping from nothing

Starting point: what does a computer actually execute? The bootstrap work
began with writing a program in raw hex bytes — the most minimal possible
executable — then building up from there.

The `bcompiler` chain (`hex1 → hex2a → hex3 → hex4 → hex5 → bcc`) is the
core of this stage: each hex-level stage bootstraps the next, adding one
feature at a time, until you arrive at a usable C-ish compiler. Alongside
it sits `assembly-toy-language/` with NASM and FASM examples, and
`bootstrap-nani-compiler/` exploring self-hosting from assembly into C.

**Lesson carried forward:** *You don't understand a layer until you've
built it from scratch.* Every later kernel reached for the ELF header or
the linker script with that grounding intact.

---

## KairosOS — the first real kernel

The plan was ambitious: a C kernel with a Lua userland and Awesome WM as
the desktop. It did not reach the desktop. It did reach a booting kernel,
basic syscalls, and a libc that linked.

Architecture: `kairos_kernel/` + `kairos_libc/` + `kairos_userspace/`,
built against an `x86_64-kairos-elf` cross-compiler target for GCC and
Binutils. The libc question loomed large — which headers do you actually
need? Freestanding vs. hosted environments. The `__STDC_HOSTED__` macro
as the dividing line. The custom libc was a study in *what you actually
need to get `printf` working*.

KairosOS v2 rebuilt around a `Jamroot` build system, added docs, and
attempted an LLVM/Clang toolchain. The Lua integration was still too
ambitious. The build system was still fragile.

**Lesson carried forward:** *Scope your first kernel to what you can
debug, not what you can imagine.* Also: a custom libc is always more work
than expected, and always worth it.

---

## Voleta — getting serious about toolchains

Named for "violet" in French. Where Kairos taught that the toolchain *is*
the project, Voleta treated it that way from the start: three sibling
trees for kernel, libc, and a naked GCC/Binutils cross-toolchain built
from source.

The libc here was a refinement of what Kairos started — cleaner layering,
better separation between freestanding and hosted pieces. The target
triple became `x86_64-voleta-elf`. Sysroot, multilib, and cross-compilation
stopped being mysteries and became tools.

The D exokernel detour (`05-exokernel-d/`) happened in this era: a
barebones kernel written in D, testing whether D's metaprogramming could
pay off at the kernel level. D's runtime assumptions about OS services
turned out to be load-bearing in ways that hurt at the bare-metal layer.

**Lesson carried forward:** *The toolchain is not a dependency — it's a
first-class component of your OS.* And: don't pick a language whose
runtime assumes the thing you're trying to build.

---

## IsmenaOS — the Swift runtime that never was

The idea: a C/Assembly kernel with a Swift runtime for userspace. What
got built: a C kernel, a custom libc (the familiar parts), and an
`ismenaos-runtime/` placeholder that never shipped.

Swift assumes Darwin or Linux. The amount of runtime support the language
expects from the host was underestimated. The honest README line from
that era — *"This project has been put on hold for further research"* —
is still the right summary.

The libc is the through-line. Every kernel so far has needed a custom
libc, and each iteration has gotten better at it. IsmenaOS's libc was the
best of the C-kernel generation.

**Lesson carried forward:** *Don't couple your kernel to a language
runtime you don't control.*

---

## AstraeaOS — back to fundamentals

After IsmenaOS's ambition, a return to basics. `03-astraea/` is a single
directory: `boot.s`, `kernel.c`, `linker.ld`, and a README pointing to
the OSDev barebones tutorial. It builds against the Voleta cross-toolchain
and boots under QEMU.

The minimal viable kernel: BIOS → bootloader → protected mode → kernel
entry. Nothing more. What Kairos needed 500+ files for, the barebones
kernel does with a handful.

**Lesson carried forward:** *Sometimes the most educational project is
the smallest one.* The boot sequence, in particular, only really clicks
when you've stripped everything else away.

---

## TerranoxOS — everything applied

The current project (lives outside this repo). The short version of what
each earlier kernel contributed:

- **KairosOS** → libc architecture and the cross-compiler approach.
- **Voleta** → toolchain as a first-class component.
- **D exokernel** → exokernel ideas that fed into the capability design.
- **IsmenaOS** → don't couple the kernel to an external runtime.
- **AstraeaOS** → understand every byte of your boot sequence.

The syscall ABI is deliberate rather than ad-hoc. Capability tokens
replace ACLs for permission management. The ELF loader parses binaries
in the kernel directly — the hex-era bootstrapping work finally pays
rent.

---

## Meta-lessons

Six kernels in, the patterns that hold up beyond OS development:

1. **Build the tools first.** The toolchain and libc work was always
   more valuable than the kernel features it enabled.
2. **Scope to what you can debug.** The Lua desktop was too far from
   where the real learning was.
3. **Rewrite strategically.** Each kernel wasn't "starting over" — it
   was applying lessons from the last one.
4. **Understand every layer you depend on.** Hex → assembly → C → OS.
   Skip a layer and you'll hit a wall at it eventually.
5. **The incomplete project is still valuable.** None of these kernels
   run a desktop environment. All of them taught something that made
   the next one better.
