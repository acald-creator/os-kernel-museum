ARCH = i386
CPU_FAMILY = x86
VOLETA_GCC = /mnt/voleta-naked-toolchain/usr/bin/i386-voletaos-elf-gcc
VOLETA_CFLAGS = -O2 -g -ffreestanding -Wall -Wextra
VOLETA_TARGET_FLAGS =
SYSROOT = sysroot

DIR = voletalib
INC = $(DIR)/include
LIBC_DIR = $(DIR)/libc

LIBC_CRT_DIR = $(DIR)/crt
LIBC_CRT_SOURCES = $(LIBC_CRT_DIR)/$(CPU_FAMILY)/$(ARCH)/crt*.s

LIBC_STDIO_DIR = $(DIR)/libc/stdio
LIBC_STDLIB_DIR = $(DIR)/libc/stdlib
LIBC_STRING_DIR = $(DIR)/libc/string
LIBC_SOURCES = $(wildcard $(LIBC_STDIO_DIR)/*.c) \
	$(wildcard $(LIBC_STDLIB_DIR)/*.c) \
	$(wildcard $(LIBC_STRING_DIR)/*.c)

.PHONY: $(SYSROOT)

$(SYSROOT):
	$(RM) -r $(SYSROOT)
	mkdir -p $(SYSROOT)/usr
	cp -r $(INC) $(SYSROOT)/usr
	$(RM) *.o

	$(VOLETA_GCC) $(VOLETA_CFLAGS) --sysroot=$(SYSROOT) -c $(LIBC_CRT_SOURCES)

	mkdir -p $(SYSROOT)/lib
	mv *.o $(SYSROOT)/lib

	$(RM) *.o
	$(VOLETA_GCC) $(VOLETA_CFLAGS) --sysroot=$(SYSROOT) -c $(LIBC_SOURCES) -I $(INC)

	mkdir -p $(SYSROOT)/lib
	ar crs $(SYSROOT)/lib/libc.a *.o
	$(RM) *.o