# Barebones Kernel

Clone the custom toolchain - [https://gitlab.com/astraeaos-development/voleta-naked-toolchain.git](https://gitlab.com/astraeaos-development/voleta-naked-toolchain.git)

Add the executables to your paths.

`i386-voletaos-elf-as boot.s -o boot.o`

`i386-voletaos-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra`

`i386-voletaos-elf-gcc -T linker.ld -o astraeaos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc`

`qemu-system-i386 -kernel astraeaos.bin`

Reference: [https://wiki.osdev.org/Bare_Bones](https://wiki.osdev.org/Bare_Bones)