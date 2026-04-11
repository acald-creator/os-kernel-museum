bits 32

org 0x08048000

ehdr:
            db 0x7F, "ELF", 1, 1, 1, 0
    times 8 db  0
            dw  2
            dw  3
            dd  1
            dd  _start
            dd  phdr - $$
            dd  0
            dd  0
            dw  ehdrsize
            dw  phdrsize
            dw  1
            dw  0
            dw  0
            dw  0
ehdrsize    equ $ - ehdr

phdr:
            dd  1
            dd  0
            dd  $$
            dd  $$
            dd  filesize
            dd  filesize
            dd  5
            dd  0x244
phdrsize    equ $ - phdr

filesize    equ $ - $$

pos:
            push    0x08048054

label:
            push    0x08048058

getchar:
            push    0x0
            xor     ebx, ebx
            mov     ecx, esp
            mov     edx, ebx
            inc     edx
            mov     eax, 0x3
            int     0x80
            test    eax, eax
            je      exit
            pop     eax
            ret

exit:
            xor     eax, eax
            mov     ebx, eax 
            inc     eax
            int     0x80

gethex:
            call    getchar
            cmp     eax, 0x20
            jle     gethex
            cmp     eax, 0x23
            jne     .l1

.loop:
            call    getchar
            cmp     eax, 0xa
            jne     .loop
            jmp     gethex

.l1:
            cmp     eax, 0x2e
            jne     .l2
            call    getchar
            and     eax, 0xff
            add     eax, label
            mov     ebx, pos
            mov     [eax], ebx
            jmp     gethex

.l2:
            cmp     eax, 0x30
            jl      .l3
            cmp     eax, 0x3a
            jge     .l3
            sub     eax, 0x30
            ret

.l3:
            cmp     eax, 0x61
            jl      .l4
            cmp     eax, 0x67
            jge     .l4
            sub     eax, 0x57
            ret

.l4:
            and     eax, 0xff
            add     eax, label
            mov     ebx, [eax]
            mov     eax, pos
            add     eax, 0x4
            mov     eax, pos
            sub     ebx, eax
            mov     eax, ebx
            push    eax
            call    putchar
            pop     eax
            sar     eax, 0x8
            push    eax
            call    putchar
            pop     eax
            sar     eax, 0x10
            push    eax
            sar     eax, 0x18
            push    eax
            call    putchar
            pop     eax
            jmp     gethex

putchar:
            xor     ebx, ebx
            inc     ebx
            lea     ecx, [esp+0x4]
            mov     edx, ebx
            mov     eax, 0x4
            int     0x80
            ret
            
_start:
            call    gethex
            shl     eax, 0x4
            push    eax
            call    gethex
            add     [esp*1], eax
;            inc     0x0
            call    putchar
            pop     eax
            jmp     _start