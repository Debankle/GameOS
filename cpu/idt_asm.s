global load_idt

load_idt:
    mov eax, [esp + 4]
    sti
    lidt [eax]
    ret