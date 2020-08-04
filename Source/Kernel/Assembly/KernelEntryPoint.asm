[bits 32]

extern ConstructorsStart
extern ConstructosEnd
extern DestructorsStart
extern DestructosEnd

extern main
extern DeinitializeObjects
global KernelEntryPoint

KernelEntryPoint:
; Ensure that interupts are off.
cli

; Setup the stack frame.
mov ebp,esp
push ebp

; Call all constructors.
mov ebx,ConstructorsStart       ; Load the start of the constructors list into ebx.
Constructors:
    cmp ebx,ConstructosEnd      ; Check if we are at the end of the list.
    jae Constructors.Exit       ; If we are at the end of the list, exit the loop.

    call [ebx]                  ; Call the constructor.
    add ebx,4                   ; The size of one constructor function is 4 bytes in x86.
    jmp Constructors            ; Look at the next constructor in the list.

    .Exit:

; Call the main function.
call main

; Call the function to destroy registered destructors.
call DeinitializeObjects

; Call all destructors.
mov ebx,DestructorsStart        ; Load the start of the constructors list into ebx.
Destructors:
    cmp ebx,DestructosEnd       ; Check if we are at the end of the list.
    jae Destructors.Exit        ; If we are at the end of the list, exit the loop.

    call [ebx]                  ; Call the constructor.
    add ebx,4                   ; The size of one constructor function is 4 bytes in x86.
    jmp Destructors             ; Look at the next constructor in the list.

    .Exit:

; Halt the system.
cli
hlt