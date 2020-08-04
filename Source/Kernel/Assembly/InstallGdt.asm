[bits 32]

global InstallGdt

InstallGdt:
    mov eax,[esp + 4]
    lgdt [eax]

    ; Set the segments to use the new GDT.
    ; Force a far jump to load the cs segment register with our new code segment.
    jmp 0x08:ProtectedMode
    ProtectedMode:

    ; Set all other segments to the data segment descriptor.
    mov ax,0x10
    mov ds,ax
    mov ss,ax
    mov es,ax
    mov fs,ax
    mov gs,ax

    ret