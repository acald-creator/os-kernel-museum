KERNEL := ismenaos.elf

CC = clang
CFLAGS = -Wall -Wextra -O2 -pipe
INTERNALCFLAGS := \
	--target=x86_64-elf \
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
	-mno-red-zone

INTERNALLDFLAGS := \
	-fno-pic -fpie \
	-Wl,-static,-pie,--no-dynamic-linker,-ztext \
	-static-pie \
	-nostdlib \
	-Tlinker.ld \
	-z max-page-size=0x1000

C_SOURCE_FILES := $(shell find -name '*.c')
OBJECT_FILES := $(C_SOURCE_FILES:.c=.o)

.PHONY: all clean

all: $(KERNEL)

$(KERNEL): $(OBJ)
	$(CC) $(INTERNALCFLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

clean:
	rm -rf $(KERNEL) $(OBJECT_FILES)