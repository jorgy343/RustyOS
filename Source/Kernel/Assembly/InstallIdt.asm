[bits 32]

global InstallIdt

InstallIdt:
    mov eax,[esp + 4]
    lidt [eax]

    ret