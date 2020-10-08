%macro isr_no_error_code 1
global isr%1
isr%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_stub
%endmacro

%macro isr_error_code 1
global isr%1
isr%1:
    cli
    push byte %1
    jmp isr_common_stub
%endmacro

global enable_interrupts
global disable_interrupts

extern interrupt_handler

section .text

isr_common_stub:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call interrupt_handler
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    add esp, 8
    sti
    iret

enable_interrupts:
    sti
    ret

disable_interrupts:
    cli
    ret

isr_no_error_code 0
isr_no_error_code 1
isr_no_error_code 2
isr_no_error_code 3
isr_no_error_code 4
isr_no_error_code 5
isr_no_error_code 6
isr_no_error_code 7
isr_error_code 8
isr_no_error_code 9
isr_error_code 10
isr_error_code 11
isr_error_code 12
isr_error_code 13
isr_error_code 14
isr_no_error_code 15
isr_no_error_code 16
isr_error_code 17
isr_no_error_code 18
isr_no_error_code 19

isr_no_error_code 32
isr_no_error_code 33
isr_no_error_code 34
isr_no_error_code 35
isr_no_error_code 36
isr_no_error_code 37
isr_no_error_code 38
isr_no_error_code 39
isr_no_error_code 40
isr_no_error_code 41
isr_no_error_code 42
isr_no_error_code 43
isr_no_error_code 44
isr_no_error_code 45
isr_no_error_code 46
isr_no_error_code 47