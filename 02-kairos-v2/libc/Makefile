ARCH = x86_64
# freestanding compiler
FREE_CC = /mnt/kairos/free-toolchain/bin/x86_64-kairos-elf-gcc
FREE_AR = /mnt/kairos/free-toolchain/bin/x86_64-kairos-elf-ar
FREE_CFLAGS = -O2 -c -g -std=gnu99 -pipe -Wall -Wextra -Werror -ffreestanding
FREE_EXTRA_CFLAGS = -fno-pic -fno-stack-protector -nostdlib -mno-red-zone
# hosted compiler
HOSTED_CC = /mnt/kairos/hosted/bin/x86_64-kairos-elf-gcc
HOSTED_CFLAGS = -O2 -c -g -Wall -Wextra -Werror
HOSTED_EXTRA_CFLAGS = -fno-pic -fno-stack-protector -nostdlib -mno-red-zone
HOSTED_AR = /mnt/kairos/hosted/bin/x86_64-kairos-elf-ar
LDFLAGS = 
SYSROOT = /mnt/kairos-system

INC = include
LIBC_SRC = src
LIBC_CRT = crt
LIBC_CRT_SOURCES = $(LIBC_CRT)/$(ARCH)/crt*.s
LIBC_SOURCES = $(wildcard $(LIBC_SRC)/*/*.c)

.PHONY: $(SYSROOT)

$(SYSROOT):
	$(RM) -r $(SYSROOT)
	mkdir -p $(SYSROOT)/usr
	cp -r $(INC) $(SYSROOT)/usr
	$(RM) *.o

	$(HOSTED_CC) $(HOSTED_CFLAGS) $(HOSTED_EXTRA_CFLAGS) --sysroot=$(SYSROOT) -c $(LIBC_CRT_SOURCES)
	mkdir -p $(SYSROOT)/lib
	mv *.o $(SYSROOT)/lib

	$(RM) *.o
	$(HOSTED_CC) $(HOSTED_CFLAGS) $(HOSTED_EXTRA_CFLAGS) --sysroot=$(SYSROOT) -c $(LIBC_SOURCES) -I $(INC)

	mkdir -p $(SYSROOT)/lib
	$(HOSTED_AR) crs $(SYSROOT)/lib/libc.a *.o
	$(RM) *.o