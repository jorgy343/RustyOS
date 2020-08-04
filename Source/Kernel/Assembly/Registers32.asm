[bits 32]

global GetControlRegister0
global SetControlRegister0
global GetControlRegister2
global GetControlRegister3
global SetControlRegister3
global GetControlRegister4
global SetControlRegister4
global GetFlags
global SetFlags
global GetModelSpecificRegister
global SetModelSpecificRegister

GetControlRegister0:
    mov eax,cr0
    ret

SetControlRegister0:
    mov eax,[esp + 4]
    mov cr0,eax
    ret

GetControlRegister2:
    mov eax,cr2
    ret

GetControlRegister3:
    mov eax,cr3
    ret

SetControlRegister3:
    mov eax,[esp + 4]
    mov cr3,eax
    ret

GetControlRegister4:
    mov eax,cr4
    ret

SetControlRegister4:
    mov eax,[esp + 4]
    mov cr4,eax
    ret

GetFlags:
    pushfd
    pop eax
    ret

SetFlags:
    push dword [esp + 4]
    popfd
    ret

GetModelSpecificRegister:
    mov ecx,[esp + 4]
    rdmsr
    ret

SetModelSpecificRegister:
    mov ecx,[esp + 4]
    mov eax,[esp + 8]
    mov edx,[esp + 12]
    wrmsr
    ret