[bits 32]

global InstallLdt

InstallLdt:
    mov ax,[esp + 4]
    lldt ax

    ret