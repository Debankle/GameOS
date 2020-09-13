bits 32

global loader
extern kmain

section .bss
    align 4
    kernel_stack:
        resb KERNEL_STACK_SIZE

section .multiboot
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

section .text
    align 4

    loader:
        mov esp, kernel_stack + KERNEL_STACK_SIZE
        call kmain

        mov eax, 0xCAFEBABE
        jmp .loop

    .loop:
        jmp .loop

section .data
    MAGIC_NUMBER    equ 0x1BADB002
    FLAGS           equ 0
    CHECKSUM        equ -(MAGIC_NUMBER + FLAGS)

    KERNEL_STACK_SIZE equ 0x1000