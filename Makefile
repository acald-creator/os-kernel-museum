ARCH ?= i386
BOOT := build/boot-$(ARCH).bin
KERNEL := build/kernel-$(ARCH).bin
KERNEL_ELF := build/kernel-$(ARCH).elf
LINKER_SCRIPT := ismenaos-kernel/src/arch/$(ARCH)/linker.ld
BOOT_SOURCE_FILE := ismenaos-kernel/src/arch/$(ARCH)/boot.s
SWIFT_SOURCE_FILES := ismenaos-kernel/src/kernel/main.swift $(shell find ismenaos-kernel/src/kernel -name "*.swift" ! -name "main.swift")
SWIFT_BC_FILES := $(patsubst ismenaos-kernel/src/kernel/%.swift, \
    build/%.bc, $(SWIFT_SOURCE_FILES))
SWIFT_OBJECT_FILES := $(patsubst src/%.swift, \
    build/%.o, $(SWIFT_SOURCE_FILES))
LIBC_SOURCE_FILES := $(shell find ismenaos-libc/libc/src -name "*.c")
LIBC_OBJECT_FILES := $(patsubst ismenaos-libc/libc/src/%.c, \
    build/libc/%.o, $(LIBC_SOURCE_FILES))

SWIFT = swiftc
SWIFTFLAGS = -emit-library -emit-bc -static-stdlib

CC = clang
CFLAGS  = -c -g -m16 -march=i386 --target=i386-elf
LD = ld.lld
OBJCOPY = llvm-obcopy

.PHONY: all

all: $(boot) $(kernel)

$(boot):
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) $(BOOT_SOURCE_FILE) -o $(boot)

$(kernel): $(LIBC_OBJECT_FILES) $(SWIFT_OBJECT_FILES) $(LINKER_SCRIPT)
	@$(LD) -T $(LINKER_SCRIPT) -o $(KERNEL_ELF) $(LIBC_OBJECT_FILES) $(SWIFT_OBJECT_FILES)
	@$(OBJCOPY) $(KERNEL_ELF) -O binary $(kernel)

$(SWIFT_OBJECT_FILES):
	@$(foreach var,$(SWIFT_BC_FILES),mkdir -p $(shell dirname $(var));)
	$(SWIFT) $(SWIFTFLAGS) $(SWIFT_SOURCE_FILES)
	@$(foreach var,$(SWIFT_BC_FILES),mv $(shell basename $(var)) $(var);)
	@$(CC) $(CFLAGS) -c $(SWIFT_BC_FILES)
	@$(foreach var,$(SWIFT_OBJECT_FILES),mv $(shell basename $(var)) $(var);)

build/libc/%.o: ismenaos-kernel/libc/src/%.c
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) -c $< -o $@
