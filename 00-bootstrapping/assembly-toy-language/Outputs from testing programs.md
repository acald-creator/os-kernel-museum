gcc -Wall toy.c 
./a.out ; echo $?
42

wc -c a.out 
16464 a.out

gcc -Wall -s toy.c 
./a.out ; echo $?
42

wc -c a.out 
14328 a.out

gcc -Wall -s -O3 toy.c 
./a.out ; echo $?
42

wc -c a.out 
14328 a.out

---

nasm -f elf tiny.asm
gcc -m32 -Wall -s tiny.o
wc -c a.out 
13656 a.out

nasm -f elf tiny2.asm
gcc -Wall -s tiny2.o
/usr/bin/ld: tiny2.o: in function `_start':
tiny2.asm:(.text+0x0): multiple definition of `_start'; /usr/lib/gcc/x86_64-linux-gnu/9/../../../../x86_64-linux-gnu/lib/../lib/Scrt1.o:(.text+0x0): first defined here
/usr/bin/ld: i386 architecture of input file `tiny2.o' is incompatible with i386:x86-64 output
/usr/bin/ld: /usr/lib/gcc/x86_64-linux-gnu/9/../../../../x86_64-linux-gnu/lib/../lib/Scrt1.o: in function `_start':
(.text+0x24): undefined reference to `main'
collect2: error: ld returned 1 exit status

gcc -m32 -Wall -s -nostartfiles -tiny2.o

./a.out ; echo $?
Segmentation fault (core dumped)
139

---

nasm -f elf tiny3.asm 
gcc -m32 -Wall -s -nostartfiles tiny3.o
./a.out ; echo $?
42

wc -c a.out 
13068 a.out

---
fasm tiny4.asm
gcc -m32 -Wall -s nostdlib tiny4.o
./a.out ; echo $?
42
wc -c aout
8696 a.out

---
nasm -f elf tiny4.asm
gcc -m32 -Wall -s -nostdlib tiny4.o
./a.out ; echo $?
42

wc -c a.out 
12780 a.out

---
Generate list

nasm -f elf tiny4.asm -l tiny.lst

ld -m elf_i386 -s tiny5.o
./a.out ; echo $?
42

wc -c a.out 
4240 a.out

objdump -x a.out

a.out:     file format elf32-i386
a.out
architecture: i386, flags 0x00000102:
EXEC_P, D_PAGED
start address 0x08049000

Program Header:
    LOAD off    0x00000000 vaddr 0x08048000 paddr 0x08048000 align 2**12
         filesz 0x00000074 memsz 0x00000074 flags r--
    LOAD off    0x00001000 vaddr 0x08049000 paddr 0x08049000 align 2**12
         filesz 0x00000007 memsz 0x00000007 flags r-x

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         00000007  08049000  08049000  00001000  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
SYMBOL TABLE:
no symbols

---
fasm tiny2.asm

gcc -m32 -Wall -s -nostdlib tiny2.o
./a.out ; echo $?
42

wc -c a.out
8688

--

ld -m elf_i386 -s tiny2.o
./a.out ; echo $?

wc -c a.out
4240 a.out

objdump -x a.out 

a.out:     file format elf32-i386
a.out
architecture: i386, flags 0x00000102:
EXEC_P, D_PAGED
start address 0x08049000

Program Header:
    LOAD off    0x00000000 vaddr 0x08048000 paddr 0x08048000 align 2**12
         filesz 0x00000074 memsz 0x00000074 flags r--
    LOAD off    0x00001000 vaddr 0x08049000 paddr 0x08049000 align 2**12
         filesz 0x00000007 memsz 0x00000007 flags rwx

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .flat         00000007  08049000  08049000  00001000  2**2
                  CONTENTS, ALLOC, LOAD, CODE
SYMBOL TABLE:
no symbols

---
nasm elf.asm -f bin

file elf
elf: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), statically linked, no section header

chmod +x elf
./elf ; echo $?
42

wc -c elf
91 elf

nasm elf2.asm -f bin
chmod +x elf2
./elf2 ; echo $?
42

wc -c elf2
84 elf2

---
nasm elf3 -f bin

file elf3
elf3: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), statically linked, no section header

chmod +x elf3
./elf3 ; echo $?
42

wc -c elf3