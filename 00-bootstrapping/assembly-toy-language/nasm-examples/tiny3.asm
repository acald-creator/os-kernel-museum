; tiny.asm
bits 32
extern _exit
global _start
section .text
_start:
    push dword 42
    call _exit