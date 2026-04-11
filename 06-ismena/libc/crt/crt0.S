.global _start

.extern __ismenaos_main
.extern ismenaos_exit

_start:
    call __ismenaos_main

wait:
    hlt
    jmp wait
