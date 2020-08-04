[bits 32]

global outb
global outw
global outl
global inb
global inw
global inl

outb:
    mov al,[esp + 4]
    mov dx,[esp + 8]
    out dx,al
    ret

outw:
    mov ax,[esp + 4]
    mov dx,[esp + 8]
    out dx,ax
    ret

outl:
    mov eax,[esp + 4]
    mov dx,[esp + 8]
    out dx,eax
    ret

inb:
    mov dx,[esp + 4]
    in al,dx
    ret

inw:
    mov dx,[esp + 4]
    in ax,dx
    ret

inl:
    mov dx,[esp + 4]
    in eax,dx
    ret