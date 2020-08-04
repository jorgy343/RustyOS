[bits 64]

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
    mov rax,cr0
    ret

SetControlRegister0:
    mov rax,[rsp + 4]
    mov cr0,rax
    ret

GetControlRegister2:
    mov rax,cr2
    ret

GetControlRegister3:
    mov rax,cr3
    ret

SetControlRegister3:
    mov rax,[rsp + 4]
    mov cr3,rax
    ret

GetControlRegister4:
    mov rax,cr4
    ret

SetControlRegister4:
    mov rax,[rsp + 4]
    mov cr4,rax
    ret

GetFlags:
    pushfq
    pop rax
    ret

SetFlags:
    push qword [rsp + 4]
    popfq
    ret

GetModelSpecificRegister:
    mov ecx,[rsp + 4]
    rdmsr
    ret

SetModelSpecificRegister:
    mov ecx,[rsp + 4]
    mov eax,[rsp + 8]
    mov edx,[rsp + 12]
    wrmsr
    ret