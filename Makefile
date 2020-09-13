C_SOURCES = $(wildcard drivers/*.c kernel/*.c libc/*.c cpu/*.c)
S_SOURCES = $(wildcard boot/*.s drivers/*.s cpu/*.s kernel/*.s)

C_OBJECTS = ${C_SOURCES:.c=.o}
S_OBJECTS = ${S_SOURCES:.s=.o}

CC = gcc
CFLAGS = -g -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
			-nostartfiles -nodefaultlibs -c -Wall -Wextra -Werror
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

.PHONY: all kernel.x86 build

all: kernel.x86

kernel.x86: $(C_OBJECTS) $(S_OBJECTS)
	ld $(LDFLAGS) $^ -o kernel.x86

GameOS.iso: kernel.x86
	cp kernel.x86 iso/boot/kernel.x86
	grub-file --is-x86-multiboot iso/boot/kernel.x86
	grub-mkrescue -o $@ iso

build: GameOS.iso
	@echo "Built GameOS.iso"

run: GameOS.iso
	bochs -f bochsrc.txt -q

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf $(C_OBJECTS) $(S_OBJECTS) kernel.x86 iso/boot/kernel.x86 GameOS.iso bochslog.txt