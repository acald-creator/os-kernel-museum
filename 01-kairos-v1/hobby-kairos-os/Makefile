ARCH ?= x86_64
#
AR = /mnt/kairos/hosted/bin/ar
LD = /mnt/kairos/hosted/bin/ld
NM = /mnt/kairos/hosted/bin/nm
OBJDUMP = /mnt/kairos/hosted/bin/objdump
OBJCOPY = /mnt/kairos/hosted/bin/objcopy
#
CC = /mnt/kairos/hosted/bin/x86_64-kairos-elf-gcc
CFLAGS = -std=gnu99 -fpic -shared -mno-red-zone
INTERNAL_CFLAGS = -I/usr/local/terra/include/terra -L/usr/local/terra/lib -lterra -ldl
LDFLAGS =
INTERNAL_LDFLAGS =
#
KAIROS_LIBC_DIR = kairos_libc
LIBC_CRT_DIR = $(KAIROS_LIBC_DIR)/crt
LIBC_CRT_SOURCES = $(LIBC_CRT_DIR)/$(ARCH)/crt*.s
#
LIBC_DIR = libc
LIBC_SRC_DIR = src
INCLUDE = $(KAIROS_LIBC_DIR)/$(LIBC_DIR)/include
LIBC_SOURCES = $(KAIROS_LIBC_DIR)/$(LIBC_SRC_DIR)/*/*.c
#
KAIROS_USERSPACE_DIR = kairos_userspace
#
SYSROOT = /mnt/kairos-chroot

.PHONY: $(SYSROOT)

$(SYSROOT):
	$(RM) -r $(SYSROOT)
	mkdir -p $(SYSROOT)/usr
	cp -r $(INCLUDE) $(SYSROOT)/usr
	$(RM) *.o

	$(CC) $(CFLAGS) $(INTERNAL_CFLAGS) --sysroot=$(SYSROOT) -c $(LIBC_CRT_SOURCES)
	mkdir -p $(SYSROOT)/lib
	mv *.o $(SYSROOT)/lib

	$(RM) *.o
	$(CC) $(CFLAGS) $(INTERNAL_CFLAGS) --sysroot=$(SYSROOT) -c $(LIBC_SOURCES) -I $(INCLUDE)

	mkdir -p $(SYSROOT)/lib
	$(AR) crs $(SYSROOT)/lib/libc.a *.o
	$(RM) *.o