KERNEL := kairos.elf
ARCH ?= x86_64
CC ?= /mnt/kairos/toolchain/bin/$(ARCH)-kairos-elf-gcc
LD ?= /mnt/kairos/toolchain/bin/$(ARCH)-kairos-elf-ld
CFLAGS 	?= -Wall -Wextra -Werror -O2 -pipe
LDFLAGS ?=
KAIROS_CFLAGS := \
	-I. \
	-nostdlib \
	-std=gnu99 \
	-ffreestanding \
	-fno-stack-protector \
	-fno-pic \
	-mno-80387 \
	-mno-mmx \
	-mno-3dnow \
	-mno-sse \
	-mno-sse2 \
	-mno-red-zone \
	-mcmodel=kernel \
	-MMD

KAIROS_LDFLAGS := \
	-T./arch/$(ARCH)/linker.ld \
	-nostdlib \
	-zmax-page-size=0x1000

SRC_FILES := kernel.c
OBJECTS := $(SRC_FILES:.c=.o)
HEADER_DEPS := $(SRC_FILES:.c=.d)

.PHONY: all
all: $(KERNEL)

$(KERNEL): $(OBJECTS)
	$(LD) $(OBJECTS) $(LDFLAGS) $(KAIROS_LDFLAGS) -o $@

-include $(HEADERS_DEPS)
%.o: %.c
	$(CC) $(CFLAGS) $(KAIROS_CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(KERNEL) $(OBJECTS) $(HEADER_DEPS)

# mkdir build && cd build
# git clone https://github.com/limine-bootloader/limine.git --branch=v2.0-branch-binary --depth=1
# make -C limine
# mkdir -p iso_root
# cp ../kairos.elf ../limine.cfg limine/limine.sys limine/limine-cd.bin limine/limine-eltorito-efi.bin iso_root/
# xorriso -as mkisofs -b limine-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot limine-eltorito-efi.bin -efi-boot-part --efi-boot-image --protective-msdos-label iso_root/ -o image.iso
# dd if=/dev/zero bs=1M count=0 seek=64 of=image.hdd
# sudo parted -s image.hdd mklabel gpt
# sudo parted -s image.hdd mkpart ESP fat32 2048s 100%
# sudo parted -s image.hdd set 1 esp on
# ./limine/limine-install image.hdd
# USED_LOOPBACK=$(sudo losetup -Pf --show image.hdd)
# sudo mkfs.fat -F 32 ${USED_LOOPBACK}p1
# mkdir -p img_mount
# sudo mount ${USED_LOOPBACK}p1 img_mount
# sudo mkdir -p img_mount/EFI/BOOT
# sudo cp -v ../kairos.elf ../limine.cfg limine/limine.sys img_mount/
# sudo cp -v limine/BOOTX64.EFI img_mount/EFI/BOOT/
# sync
# sudo umount img_mount
# sudo losetup -d ${USED_LOOPBACK}
# sudo qemu-system-x86_64 -M q35 -m 2G -cdrom image.iso