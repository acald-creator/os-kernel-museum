#!/bin/bash
# DO NOT USE

clang --target=x86_64-elf \
	-c \
	-I. \
	-std=gnu11 \
	-ffreestanding \
	-nostdlib \
	-fno-stack-protector \
	-fno-pic -fpie \
	-mno-80387 \
	-mno-mmx \
	-mno-3dnow \
	-mno-sse \
	-mno-sse2 \
	-mno-red-zone kernel.c -o kernel.o

ld.lld -T linker.ld -z max-page-size=0x1000 kernel.o -o ismenaos.elf

llvm-objcopy -O binary ismenaos.elf ismenaos.bin

xorriso -as mkisofs -b limine-cd.bin \
	-no-emul-boot \
	-boot-load-size 4 \
	-boot-info-table \
	--efi-boot limine-eltorito-efi.bin \
	-efi-boot-part \
	--efi-boot-image \
	--protective-msdos-label iso_root -o ismenaos.iso