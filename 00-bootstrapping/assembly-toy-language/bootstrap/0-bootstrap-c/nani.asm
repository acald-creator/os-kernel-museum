[BITS 32]

EXTERN _exit
GLOBAL nani_main
SECTION .text

nani_main:
    mov eax, 0
    call _exit