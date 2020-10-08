global load_gdt

load_gdt:
    mov eax, [esp+4]
    lgdt [eax]
    jmp reload_segments

reload_segments:
    jmp 0x8:.reload_cs

.reload_cs:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret

