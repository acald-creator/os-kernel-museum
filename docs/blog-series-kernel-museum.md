# Blog Series: The OS Kernel Museum

> "Four kernels later — the journey from KairosOS to TerranoxOS"

A blog series documenting the full OS kernel lineage. Not a tutorial —
a narrative about what was built, what broke, what was learned, and what
carried forward at each stage.

**MVP project:** #48 OS Kernel Museum
**Repo:** Monorepo with each kernel in its own directory + QEMU boot scripts
**Target audience:** Developers curious about OS development, systems
programmers, and anyone who's considered writing a kernel

---

## The Timeline

| Era | Kernel | Language | Key innovation | Where the code lives |
|---|---|---|---|---|
| ~2020 | Assembly experiments | ASM | Hex bootstrapping, bare metal | USB: `assembly-toy-language` |
| ~2020 | KairosOS v1 | C | First real kernel + libc + userspace | USB: `hobby-kairos-os` (501 files) |
| ~2020 | KairosOS v2 | C | Refined build, docs, GNU/LLVM toolchain | USB: `os-kairos` (567 files) |
| 2021 | Voleta | C | Custom libc, GCC/Binutils cross-toolchain | GitHub: `voleta-*` repos |
| 2021 | D Exokernel | D | Exokernel architecture experiment | GitHub: `exokernel-dlang` |
| 2021 | IsmenaOS | C/ASM | Swift runtime concept, custom libc | GitHub (nebula-aac): `ismena-os` |
| 2022 | AstraeaOS | ASM | Pure assembly kernel | GitHub: `astraeaos` |
| Current | TerranoxOS | C/ASM | 91-syscall ABI, capability tokens, ELF loader | Private/in progress |

---

## Series Outline

### Post 1: "Why I keep writing kernels"
**Type:** Introduction / narrative
**Length:** ~1500 words

**Content:**
- The hook: "I've written six operating system kernels. None of them run
  anything useful. Here's why I keep doing it."
- What draws you to OS development — the gap between "I use Linux" and
  "I understand what Linux does"
- The progression: each kernel wasn't a failure, it was a prerequisite
- What this series covers and who it's for
- Preview the timeline graphic (visual of the lineage)

**Technical depth:** Light. This is the narrative hook.

**Call to action:** Link to the museum repo, invite readers to boot each
kernel in QEMU and follow along.

---

### Post 2: "Bootstrapping from nothing — assembly and hex"
**Type:** Technical narrative
**Length:** ~2500 words
**Source:** USB `assembly-toy-language` (128 files)

**Content:**
- Starting point: what does a computer actually execute?
- Writing a program in raw hex bytes — the most minimal possible executable
- Building up: hex → NASM assembler → tiny ELF binaries
- The `bcompiler` chain: hex1 → hex2a → hex3 → hex4 → hex5 → bcc
  (each stage bootstraps the next, adding features)
- What it feels like to write software where there's truly nothing
  beneath you
- Lesson: "You don't understand a layer until you've built it from scratch"

**Code highlights:**
- The minimal ELF header written in hex
- A tiny NASM program that prints "Hello"
- The bootstrap chain — how each stage adds one feature

**Images:**
- Hex dump of the first working binary
- Diagram: the bootstrap chain stages

---

### Post 3: "KairosOS — my first real kernel"
**Type:** Technical deep dive
**Length:** ~3000 words
**Source:** USB `hobby-kairos-os` (501 files) + `os-kairos` (567 files)

**Content:**
- The plan: C kernel with Lua userland and Awesome WM as desktop
  (ambitious? yes. completed? no. educational? absolutely.)
- Architecture: `kairos_kernel/` + `kairos_libc/` + `kairos_userspace/`
- Building the cross-compiler: `x86_64-kairos-elf` target for GCC/Binutils
- The libc problem: which headers do you need? Freestanding vs. hosted
  environments. The `__STDC_HOSTED__` macro.
- Custom libc implementation: what you actually need to get `printf` working
- What worked: kernel boots, basic syscalls, libc links
- What didn't: Lua integration was too ambitious, build system was fragile
- KairosOS v2: Jamroot build system, better docs, LLVM/Clang attempt
- Lesson: "Scope your first kernel to what you can debug, not what you
  can imagine"

**Code highlights:**
- The GCC cross-compiler configure flags and why each matters
- A minimal kernel entry point
- The custom libc `stdio.h` vs. the real thing
- The Jamroot build file (unusual choice — worth discussing why)

**Images:**
- Directory structure diagram
- The toolchain build pipeline
- QEMU screenshot (if it boots)

---

### Post 4: "Voleta — getting serious about toolchains"
**Type:** Technical deep dive
**Length:** ~2500 words
**Source:** GitHub `voleta-operating-system-kernel`, `voleta-custom-libc`,
`voleta-naked-toolchain` (742 files)

**Content:**
- Named "Violet" in French — the aesthetic matters even in kernels
- The shift: KairosOS taught that the toolchain IS the project
- Building a naked GCC/Binutils toolchain from source (742 files!)
- The custom libc — what Kairos started, Voleta refined
- Cross-compilation deep dive: sysroot, target triplets, multilib
- The exokernel detour: `exokernel-dlang` — trying D language for a
  kernel. What worked (D's metaprogramming), what didn't (D's runtime
  assumptions about OS services)
- Lesson: "The toolchain is not a dependency — it's a first-class
  component of your OS"

**Code highlights:**
- GCC configure for a custom `x86_64-voleta-elf` target
- Voleta's libc vs. Kairos's libc — what changed
- The D exokernel experiment: what a kernel looks like in D

**Images:**
- Toolchain build pipeline diagram
- Sysroot directory layout
- Code comparison: C kernel vs. D kernel

---

### Post 5: "IsmenaOS — the Swift runtime that never was"
**Type:** Technical narrative + postmortem
**Length:** ~2000 words
**Source:** GitHub (nebula-aac) `ismena-os`, `ismena-custom-libc`

**Content:**
- The idea: C/Assembly kernel with a Swift runtime for userspace
- Named after learning AstraeaOS basics — IsmenaOS was "the second project"
- What actually got built: C kernel + custom libc (the familiar parts)
- The Swift runtime challenge: Swift assumes Darwin/Linux, not a custom OS.
  The amount of runtime support needed was underestimated.
- What got put on hold: "This project has been put on hold for further
  research" — the honest README line
- The libc is the bridge: every kernel so far needed a custom libc,
  and each iteration got better at it
- Lesson: "Don't couple your kernel to a language runtime you don't
  control"

**Code highlights:**
- IsmenaOS kernel entry vs. Voleta's — evolution visible
- The libc that keeps getting rewritten
- What a Swift runtime would need from the kernel (and why that's hard)

---

### Post 6: "AstraeaOS — back to pure assembly"
**Type:** Technical narrative
**Length:** ~1500 words
**Source:** GitHub `astraeaos` (17 files, Assembly)

**Content:**
- After IsmenaOS's ambition, a return to fundamentals
- Pure assembly kernel — no C, no libc, no toolchain complexity
- What 17 files of assembly teaches you that 500 files of C didn't
- The minimal viable kernel: what do you actually need to boot?
- Boot sequence: BIOS → bootloader → protected mode → kernel
- Lesson: "Sometimes the most educational project is the smallest one"

**Code highlights:**
- The entire boot sequence in assembly
- GDT setup, protected mode switch
- Comparison: what Kairos needed 500+ files for, AstraeaOS does in 17

**Images:**
- The 17-file directory listing (the whole OS fits on screen)
- QEMU boot screenshot

---

### Post 7: "TerranoxOS — everything I learned, applied"
**Type:** Architecture overview + forward-looking
**Length:** ~3000 words
**Source:** TerranoxOS (active project, being built with Claude — has CLAUDE.md)

**Content:**
- The culmination: every kernel taught something that TerranoxOS uses
- The AI-assisted development angle: building an OS kernel with Claude.
  What Claude handles well (boilerplate, syscall table scaffolding,
  documentation), where you lead (architecture, capability design,
  hardware-specific debugging)
- The 91-syscall ABI — why 91? What each syscall does. How the ABI
  was designed (lessons from KairosOS's ad-hoc approach)
- Capability tokens: 128-bit tokens for permission management. Why
  capabilities instead of ACLs. The revocation chain.
- The ELF loader: parsing ELF binaries in the kernel. Direct application
  of the assembly-era hex bootstrapping knowledge.
- What carried forward from each kernel:
  - KairosOS → libc architecture, cross-compiler approach
  - Voleta → toolchain-as-first-class-component
  - IsmenaOS → don't couple to external runtimes
  - AstraeaOS → understand every byte of your boot sequence
  - D exokernel → exokernel ideas in the capability design
- What's next for TerranoxOS

**Code highlights:**
- The syscall table (all 91)
- A capability token structure
- ELF header parsing in kernel space

**Images:**
- TerranoxOS architecture diagram
- Capability token DAG visualization (connects to #9)
- Syscall categories breakdown

---

### Post 8: "What six kernels taught me about software"
**Type:** Retrospective / lessons learned
**Length:** ~2000 words

**Content:**
- The meta-lessons that apply beyond OS development:
  1. **Build the tools first.** The toolchain/libc work was always more
     valuable than the kernel features.
  2. **Scope to what you can debug.** KairosOS's Lua desktop was too far
     from where the real learning was.
  3. **Rewrite strategically.** Each kernel wasn't "starting over" — it
     was applying lessons from the last one.
  4. **Understand every layer you depend on.** Hex bootstrapping → assembly →
     C → OS. Skip a layer and you'll hit a wall.
  5. **The incomplete project is still valuable.** None of these kernels
     run a desktop environment. All of them taught something that made
     the next one better.
- How OS development changed the way you think about:
  - Docker containers (they're just namespaces + cgroups — you've built
    the things they abstract over)
  - System calls (you designed 91 of them)
  - Memory management (you've implemented it from scratch)
  - Security (capability tokens came from understanding privilege at
    the lowest level)
- The honest ending: "I'll probably write a seventh kernel"

---

## Series Production Plan

| Post | Draft deadline | Dependencies |
|---|---|---|
| 1. Why I keep writing kernels | Week 1 | None — narrative only |
| 2. Bootstrapping from nothing | Week 2 | Copy USB `assembly-toy-language` + `bcompiler` to repo |
| 3. KairosOS | Week 3 | Copy USB `hobby-kairos-os` + `os-kairos` to repo, try QEMU boot |
| 4. Voleta | Week 4 | Already on GitHub, add QEMU scripts |
| 5. IsmenaOS | Week 5 | Already on GitHub (nebula-aac), copy to museum repo |
| 6. AstraeaOS | Week 6 | Already on GitHub, add QEMU scripts |
| 7. TerranoxOS | Week 7 | Active project, being built with Claude. Content depends on what's public by then |
| 8. Lessons learned | Week 8 | None — retrospective |

## Technical Requirements for the Museum Repo

Each kernel directory should have:
- Original source code (preserved exactly)
- `README.md` with what it is, when it was written, what it taught
- `boot.sh` — QEMU boot script (where possible)
- `Makefile` or build instructions
- `LESSONS.md` — what carried forward to the next kernel

```
os-kernel-museum/
  01-assembly-bootstrap/     # hex + NASM experiments
  02-kairos-v1/              # hobby-kairos-os
  03-kairos-v2/              # os-kairos
  04-voleta/                 # kernel + libc + toolchain
  05-exokernel-d/            # D language experiment
  06-ismena/                 # IsmenaOS + libc
  07-astraea/                # Pure assembly kernel
  08-terranox/               # Current (or reference docs)
  TIMELINE.md                # Visual timeline
  README.md                  # Series overview
```

## Cross-links to Other MVP Projects

| Blog post | Links to |
|---|---|
| Post 2 (bootstrapping) | #41 Mini Language Interpreter, #44 Cross-Compiler Toolchain |
| Post 3 (KairosOS libc) | #43 WASM Micro-Runtime (kairos-wasm-libc heritage) |
| Post 4 (toolchains) | #44 Cross-Compiler Toolchain Builder |
| Post 6 (AstraeaOS) | #7 ELF Binary Inspector |
| Post 7 (TerranoxOS) | #5 Syscall Reference Explorer, #9 Capability Token Visualizer, #54 WinPE Explorer |
| Post 8 (lessons) | Main Stack Challenge series intro |
