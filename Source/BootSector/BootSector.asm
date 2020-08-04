%define StackSegment                    0x9000      ; Because this is a segment it is really address 0x90000
%define StackOffset                     0xF000

%define KernelFileLocation              0x200000
%define KernelLocation                  0x100000

%define MemoryMapEntryCount             0x600
%define MemoryMapEntryStart             0x608

%define VesaSegment                     0x1000      ; Because this is a segment it is really address 0x10000.
%define VesaInformationBufferOffset     0x0
%define VesaVideoModeCountOffset        0x200
%define VesaVideoModeListOffset         0x300
%define VesaVideoModeDefinitionsOffset  0x500

[bits 16]
[org 0x7C00]


;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;
;;	Stage 1
;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;
jmp 0x0:Stage1Start ; Ensure that our cs segment is setup properly.

Stage1Start:
cli                 ; Turn off interrupts.

; Setup the stack.
mov ax,StackSegment
mov ss,ax           ; Stack segment begins at 0x90000.
mov sp,StackOffset  ; Stack pointer points to 0x9FB00. Stack grows down, allow for some underflow.

xor ax,ax
mov ds,ax           ; Set the ds segment to 0x0.

mov [BootDevice],dl ; Save the boot device number.


; Retrieve and save the disk geometry.
call GetDiskGeometry


LoadStage2:

; Get offset to first cluster
mov ax,0x2000       ; We will load all sectors and clusters
mov es,ax           ; to the address 0x20000
xor bx,bx           ; Offset to load File System Definition: 0x0

; Load the File System Definition into memory
; Assumming the sector size is 512 bytes
mov ax,1            ; File system definition start
mov si,3            ; File system definition is 3 sectors large
mov dl,[BootDevice]
call LoadSectorsCHS

; Save the file system definition to the stack
push dword [es:0x0 + 4]     ; Push cluster size (in bytes), [bp + 8]
push dword [es:0x0 + 8]     ; push cluster size (in sectors), [bp + 4]
push dword [es:0x0 + 36]    ; Push the offset (in sectors) to the first cluster, [bp]
mov bp,sp           ; So we can access data on the stack

    xor ecx,ecx     ; ecx contains cluster number, 0 is root directory
    .LoadCluster:
    push ecx                ; Cluster to read
    push dword [ss:bp + 4]  ; Push cluster size (in sectors)
    push dword [ss:bp]      ; Push the offset (in sectors) to the first cluster
    call LoadCluster
    
        xor bx,bx   ; bx contains directory entry number, 0 is first entry
        .DirectoryEntryLoop:
        mov al,[es:0x0 + bx]    ; Move attributes byte into al
        test al,0x1             ; Does directory entry exist?
        jz .SkipDirectoryEntry  ; If no, than skip this entry

        ; Load filename cluster
        push dword [es:24 + bx] ; Filename cluster
        mov ax,0x1900           ; After we are done using es
        mov es,ax               ; Set it to the location we wish to read data to
        push dword [ss:bp + 4]  ; Push cluster size (in sectors)
        push dword [ss:bp]      ; Push the offset (in sectors) to the first cluster
        call LoadCluster

        ; Compare filename
        mov si,Stage2Filename   ; First string is ds:si
        mov di,0x0              ; Second string is es:DI4
        call CompareStrings

        ; Restore es
        mov dx,0x2000
        mov es,dx

        ; Conditional jump based on the string comparasin
        cmp ax,0                ; Are they different?
        je .SkipDirectoryEntry  ; If yes, than skip this entry

            ; We found stage 2
            ; Load stage 2 then jump to stage 2
            mov ecx,[es:bx + 8]     ; First cluster
            mov ax,0x7E0            ; es contains the memory location to load to
            mov es,ax
            .LoadFile:
            push ecx                ; Cluster to read
            push dword [ss:bp + 4]  ; Push cluster size (in sectors)
            push dword [ss:bp]      ; Push the offset (in sectors) to the first cluster
            call LoadCluster

            ; Increment es by the (cluster size) right shift (4)
            mov ax,es           ; Stores es into ax
            mov dx,[bp + 8]     ; The size of a cluster in bytes
            shr dx,4            ; Right shift by 4 to make it a segment address
            add ax,dx           ; Increment ax by dx
            mov es,ax           ; Move the incremented address in ax into es

            ; Get next cluster in the cluster chain
            mov dx,es           ; Save es into dx
            mov ax,0x2000       ; Move 0x20000 into es
            mov es,ax           ; This is our 'scratch' memory area

            xchg eax,ecx        ; xchg takes up less space then mov
            call GetNextClusterInChain
            xchg eax,ecx

            mov es,dx           ; Restore es

            cmp ecx,0xFFFFFFFE  ; Was this cluster the last cluster?
            jne .LoadFile       ; It wasn't, so load the next cluster into memory

            mov sp,bp           ; Clean up the stack

            jmp Stage2Start

        .SkipDirectoryEntry:
        add bx,64           ; Offset to next directory entry
        cmp bx,[ss:bp + 8]  ; Is offset past cluster size (in bytes)
        jl .DirectoryEntryLoop  ; If no, than search next directory entry

    ; If yes, than load in next cluster chain
    xchg eax,ecx            ; xchg takes up less space then mov
    call GetNextClusterInChain
    xchg eax,ecx

    ; If we are at the last cluster in the chain,
    ; than the file doesn't exist; hang the system
    cmp ecx,0xFFFFFFFE
    jne .LoadCluster

cli
hlt


;;;;;;;;;;;;;;;;;
;;  LoadCluster
;;
;;  Parameters:
;;  es      LocationToLoad
;;  dword   ClusterNumber           ; bp + 12
;;  dword   ClusterSizeInSectors    ; bp + 8
;;  dword   FirstClusterOffset      ; bp + 4
;;
;;  Returns:
;;
;;;;;;;;;;;;;;;;;
LoadCluster:
enter 0,0
pushad

; Multiply cluster number by sectors per cluster
mov eax,[ss:bp + 12]    ; eax contains cluster number
xor edx,edx             ; Clear edx for mul
mul dword [ss:bp + 8]   ; edx:eax * ebx => edx = high dword, eax = low dword
add eax,[ss:bp + 4]     ; Add the first cluster offset (in sectors) to cluster number

; Load current cluster into memory
xor bx,bx               ; es:bx = memory location to load sectors into
mov si,[ss:bp + 8]      ; Move cluster size (in sectors) into si
mov dl,[BootDevice]     ; Move the boot device into dl
call LoadSectorsCHS     ; Load the sectors into memory

popad
leave
ret 12


;;;;;;;;;;;;;;;;;
;;  GetNextClusterInChain
;;
;;  Parameters:
;;  eax CatNumber
;;
;;  Returns:
;;  eax contains next cat number
;;;;;;;;;;;;;;;;;
GetNextClusterInChain:
; enter 0,0
push ebx
push ecx
push edx
push esi

; Get the CAT sector
mov ecx,4           ; 4 bytes per CAT entry
xor edx,edx         ; Clear edx for mul
mul ecx             ; Multiply the CAT number by 4 (size of uint)
                    ; Result is in eax

mov ecx,512         ; Size of sector, assumed to be 512
xor edx,edx         ; Clear edx for div
div ecx             ; Divide by 512 to get the sector the CAT number resides in
push edx            ; Save the remainder as the offset into the sector

add eax,4           ; First four sectors are permanent in the file system
                    ; ax contins LBA (sector) address to load

; Load the CAT sector
xor bx,bx           ; Load sector into es:0x0
mov dl,[BootDevice]
mov si,1            ; Read one sector
call LoadSectorsCHS

; Get the next CAT number
pop ebx                 ; Recover the remainder (offset into the sector)
mov eax,[es:0x0 + ebx]  ; Get the next CAT number

pop esi
pop edx
pop ecx
pop ebx
; leave
ret


;;;;;;;;;;;;;;;;;
;;  CompareStrings
;;
;;  Parameters:
;;  ds:si = First String
;;  es:di = Second String
;;
;;  Returns:
;;  ax = 1 if strings are the same
;;  ax = 0 if strings are different
;;;;;;;;;;;;;;;;;
CompareStrings:
; enter 0,0
push cx

mov cx,11       ; Length of the stirng we are looking for (plus null)
cld             ; Compare in the forward direction
repe cmpsb      ; Compare the strings
je .Same        ; If they are the same...

.Different:
mov ax,0        ; Strings are different, ax = 0
jmp .Exit       ; Skip to the exit

.Same:
mov ax,1        ; Strings are the same, ax = 1

.Exit:

pop cx
; leave
ret


;;;;;;;;;;;;;;;;;
;;  GetDiskGeometry
;;
;;  Parameters:
;;  dl = Device
;;
;;  Returns:
;;  Fills disk geometry data structure
;;;;;;;;;;;;;;;;;
GetDiskGeometry:
; enter 0,0
pusha
push es

xor ax,ax       ; Protect us from some BIOS bugs
mov es,ax
xor di,di

mov ah,08h
int 13h

; Get sector count
mov bl,cl
and bl,00111111b
mov [DiskGeometry.SectorCount],bl

; Get cylinder count
mov bl,ch
mov bh,cl
and bh,11000000b
shr bh,6
mov [DiskGeometry.CylinderCount],bx

; Get head count
mov [DiskGeometry.HeadCount],dh

; Get drive count
mov [DiskGeometry.DriveCount],dl

pop es
popa
; leave
ret


;;;;;;;;;;;;;;;;;
;;  LBAToCHS
;;
;;  Parameters:
;;  ax = LBA Address
;;
;;  Returns:
;;  cx and dh are setup for CHS read sector call
;;;;;;;;;;;;;;;;;
LBAToCHS:
; enter 0,0
push ax
push bx
push dx

xor dx,dx           ; Dividend is dx:ax register pair
xor bh,bh           ; Divisor is in bx, clear bh
mov bl,[DiskGeometry.SectorCount]
div bx              ; dx:ax / bx => quotient: ax, remainder: dx
mov cl,dl           ; Move Sector (dl) into cl
inc cl              ; Sector is one based, add one

cmp ax,0            ; If the quotient is zero then we only
je .OnlySectors     ; have sectors, we can stop here

xor dx,dx           ; Clear out dx again
mov bl,[DiskGeometry.HeadCount]
inc bl              ; Increment max head
div bx              ; dx:ax / bx => quotient: ax, remainder: dx
jmp .Exit

.OnlySectors:
xor ax,ax           ; We only have sectors, zero out cylinder
xor dx,dx           ; We only have sectors, zero out head

.Exit:

; Setup registers for a CHS load sectors call
; Currently cl contains sector, dx contains head, and ax contains cylinder
and cl,00111111b    ; Sector only uses low six bits
mov dh,dl           ; dl contains head, move it into dh
mov ch,al           ; Move low eight bits of cylinder into ch
shl ah,6            ; Move high two bits of cylinder into bits 6 and 7 of ah
or cl,ah            ; Move high two bits of cylinder into bits 6 and 7 of cl

pop ax              ; Preserve only dl
mov dl,al           ; dh contains head so keep dh

pop bx
pop ax
; leave
ret


;;;;;;;;;;;;;;;;;
;;  LoadSectorsCHS
;;
;;  Parameters:
;;  ax = Start LBA
;;  si = Sector Count
;;  es:bx = Memory Address To Load Sectors Into
;;  dl = Device
;;
;;  Returns:
;;  Sectors are loaded into specified memory location
;;;;;;;;;;;;;;;;;
LoadSectorsCHS:
; enter 0,0
pusha

.Loop:
call LBAToCHS
push ax

xor ah,ah           ; Clear ah for the reset command
int 13h             ; Reset disk drive
xor di,di           ; Try count

; Attempt to read a sector from the disk
.Try:
mov ah,02h
mov al,1
int 13h             ; Read sector

jnc .SkipTry        ; If we read the sector, don't try again
inc di              ; Increment try count
cmp di,5            ; Try reading the sector five times
jl .Try             ; Try again if we are are <= 5 tries

; Failed to load the sector 5 times, halt the system
cli
hlt

.SkipTry:

pop ax

add bx,512
inc ax
dec si
jnz LoadSectorsCHS.Loop

popa
; leave
ret


;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;
;;	Stage 1 Data
;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;
Stage2Filename			db 'Stage2.bin',0

; Pad the rest of stage 1 with zero bytes. This also throws an error if we go over the 510 byte limit.
times 510 - ($ - $$) db 0
dw 0xAA55


;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;
;;  Stage 2
;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;
Stage2Start:

; Force video mode 03h
; This will also clear the screen
mov ah,00h
mov al,03h
int 10h


; Set the cursor position to (0, 0)
mov ah,02h          ; Set cursor command
mov bh,00h          ; Page number
mov dh,0            ; Row
mov dl,0            ; Column
int 10h             ; Set cursor position


; Create some space for the protected mode message which comes later
call PrintNewLine
call PrintNewLine


; Print the boot drive disk geometry
xor ch,ch
push MessageGeometrySectors
call PrintString
mov cl,[DiskGeometry.SectorCount]
push cx
call PrintNumber
call PrintNewLine

push MessageGeometryHeads
call PrintString
mov cl,[DiskGeometry.HeadCount]
inc cl
push cx
call PrintNumber
call PrintNewLine

push MessageGeometryCylinders
call PrintString
mov cx,[DiskGeometry.CylinderCount]
inc cx
push cx
call PrintNumber
call PrintNewLine
call PrintNewLine


; Enable the A20 line
; Check to see if the A20 line is already enabled
EnableA20:
call A20Enabled
cmp ax,0
jne EnableA20.Enabled   ; Enabled

.Disabled:
; Print a message saying it is disabled,
; but still attempt to enable it
push MessageA20Disabled
Call PrintString

; Use the BIOS to enable A20
call A20EnableBiosInterrupt
call A20Enabled
cmp ax,0
jne EnableA20.Enabled

; We were unable to enable the A20 line
push MessageA20Failed
call PrintString

; We must hang the system
cli
hlt

; A20 is enabled, we can continue
.Enabled:
push MessageA20Enabled
call PrintString
call PrintNewLine


; Get Memory Map
call GetMemoryMap


; Print the memory map entry count
push MessageMemoryMap
call PrintString

push word [MemoryMapEntryCount]
call PrintNumber
call PrintNewLine
call PrintNewLine


; Get all of the vesa information now
call GetVesaInformation


jmp Stage3Start


;;;;;;;;;;;;;;;;;
;;  A20Enabled
;;
;;  Arguments:
;;  None
;;
;;  Returns:
;;  ax = 0 if A20 is disabled
;;  ax = 1 if A20 is enabled
;;;;;;;;;;;;;;;;
A20Enabled:
    enter 0,0
    push ds
    push es

    xor ax,ax
    mov ds,ax
    mov ax,0xFFFF
    mov es,ax

    ; Check wrap around address
    cmp word [es:0x7E0E],0xAA55
    jne .Enabled

    mov word [ds:0x7DFE],0x9944
    cmp word [es:0x7E0E],0x9944
    jne .Enabled

    ; Return ax=0 if A20 is disabled
    .Disabled:
        mov ax,0
        jmp .Exit

    ; Return ax=1 if A20 is enabled
    .Enabled:
    mov ax,1

    .Exit:
    ; Set the boot signature back to 0xAA55
    ; in case we have to test the A20 line again
    mov word [ds:0x7DFE],0xAA55

    pop es
    pop ds
    leave
    ret


;;;;;;;;;;;;;;;;;
;;  A20EnableBiosInterrupt
;;
;;  Arguments:
;;  None
;;
;;  Returns:
;;  None
;;;;;;;;;;;;;;;;
A20EnableBiosInterrupt:
    enter 0,0
    push ax

    mov ax,2401h
    int 15h

    pop ax
    leave
    ret



;;;;;;;;;;;;;;;;;
;;  GetMemoryMap
;;
;;  Arguments:
;;  es:di = Memory Map Address
;;
;;  Returns:
;;  Sets memory map
;;;;;;;;;;;;;;;;
GetMemoryMap:
    enter 0,0
    pushad
    push es

    xor ax,ax
    mov es,ax

    mov di,MemoryMapEntryStart
    xor esi,esi         ; esi stores the entry count

    xor ebx,ebx         ; 0 in ebx indicates begining of map
    .Loop:
        mov dword [es:di + 20],1    ; ACPI 3.0 complient
        mov eax,0xE820      ; Memory map function
        mov ecx,24          ; We want 24 or 20 bytes at a time
        mov edx,'PAMS'      ; Required
        int 15h

        jc .Exit            ; May indicate end of list
        cmp ebx,0           ; May also indicate end of list
        je .Exit

        inc esi             ; Increment entry count
        add di,24           ; Increment memory address pointer

        jmp .Loop           ; Go to the begining of the loop.

    .Exit:

    mov di,MemoryMapEntryCount
    mov [es:di],esi     ; Store entry count in there

    pop es
    popad
    leave
    ret


;;;;;;;;;;;;;;;;;
;;  GetVesaInformation
;;
;;  Arguments:
;;  es:di = Pointer to Memory Buffer
;;
;;  Returns:
;;  Stores VESA information in memory
;;;;;;;;;;;;;;;;
GetVesaInformation:
    enter 0,0
    pusha
    push es
    push fs

    mov ax,VesaSegment
    mov es,ax
    mov di,VesaInformationBufferOffset

    mov dword [es:di],'VBE2'    ; We want VBE 2.0 information
    mov ax,4F00h        ; Vesa video mode interrupt
    int 10h

    cmp ah,0            ; Vesa [2.0] isn't supported
    jne .NotSupported

    mov ax,[es:di + 14 + 2] ; Contains segment for video mode array3
    mov fs,ax               ; Put segment in fs
    mov si,[es:di + 14]     ; Offset for video mode array

    xor cx,cx               ; cx holds video mode count
    mov di,VesaVideoModeListOffset  ; Copy the video mode array to this address

    .VideoModeLoop:
        mov ax,[fs:si]      ; Put the video mode number into ax
        add si,2            ; Increment offset for next video mode

        cmp ax,0xFFFF       ; 0xFFFF means we reached the end of the array
        je .ExitVideoModeLoop

        mov [es:di],ax      ; Save the video mode to our array
        add di,2            ; Increment the pointer to our array
        inc cx              ; Increment the video mode count
        jmp .VideoModeLoop  ; Fetch the next video mode

    .ExitVideoModeLoop:
        mov [es:VesaVideoModeCountOffset],cx            ; Save the video mode count
        mov word [es:VesaVideoModeCountOffset + 2],0    ; Video mode count is dword,
                                                        ; set high two bytes to zero

        mov bx,cx           ; Move video mode count into bx
        mov si,VesaVideoModeListOffset             ; Pointer to our video mode array
        mov di,VesaVideoModeDefinitionsOffset   ; Where we will store the video mode info

    .VideoModeInfoLoop:
        mov ax,4F01h        ; Vesa video mode interrupt
        mov cx,[es:si]      ; The video mode we want info about
        int 10h

        add si,2            ; Increment video mode pointer
        add di,256          ; Increment video mode info pointer

        dec bx              ; Exit the loop when we are done
        jnz .VideoModeInfoLoop

    push MessageVesaSupported
    call PrintString
    jmp .Exit

    ; Vesa doesn't appear to be supported so print a message saying so
    .NotSupported:
        push MessageVesaNotSupported
        call PrintString

    .Exit:

    pop fs
    pop es
    popa
    leave
    ret


;;;;;;;;;;;;;;;;;
;;  PrintString
;;
;;  Arguments:
;;  word PointerToString
;;
;;  Returns:
;;  None
;;;;;;;;;;;;;;;;;
PrintString:
    enter 0,0
    push ax
    push bx
    push si

    mov si,[bp + 4]
    .Loop:
        cmp byte [si],0
        je .Exit

        mov ah,0Eh
        mov al,[si]
        int 10h
        inc si

        jmp .Loop
    
    .Exit:

    pop si
    pop bx
    pop ax
    leave
    ret 2


;;;;;;;;;;;;;;;;;
;;  PrintCharacter
;;
;;  Arguments:
;;  word Character (low byte)
;;
;;  Returns:
;;  None
;;;;;;;;;;;;;;;;;
PrintCharacter:
    enter 0,0
    pusha

    mov ah,0Eh
    mov al,[bp + 4]
    int 10h

    popa
    leave
    ret 2


;;;;;;;;;;;;;;;;;
;;  PrintNewLine
;;
;;  Arguments:
;;  None
;;
;;  Returns:
;;  None
;;;;;;;;;;;;;;;;;
PrintNewLine:
    enter 0,0
    pusha

    ; Print \r
    mov ah,0Eh
    mov al,13
    int 10h

    ; Print \n
    mov ah,0Eh
    mov al,10
    int 10h

    popa
    leave
    ret


;;;;;;;;;;;;;;;;;
;;  PrintNumber
;;
;;  Arguments:
;;  word Number
;;
;;  Returns:
;;  None
;;;;;;;;;;;;;;;;;
PrintNumber:
    enter 0,0
    pusha

    mov ax,[bp + 4]
    mov bx,10
    mov si,.NumberString
    xor cx,cx

    .Loop:
        xor dx,dx
        div bx

        add dl,'0'
        mov [si],dl
        inc si
        inc cx

        cmp ax,0
        ja .Loop

    dec si
    .LoopPrint:
        mov ah,0Eh
        mov al,[si]
        int 10h

        dec si
        dec cx
        jnz .LoopPrint

    popa
    leave
    ret 2

    .NumberString db '000000'


;;;;;;;;;;;;;;;;;
;;  PrintNumber32
;;
;;  Arguments:
;;  dword Number
;;
;;  Returns:
;;  None
;;;;;;;;;;;;;;;;;
PrintNumber32:
    enter 0,0
    pushad

    mov ecx,[bp + 4]
    mov ebx,10
    mov si,.NumberString

    .Loop:
        xor edx,edx
        mov eax,ecx
        div ebx
        mov ecx,eax

        add dl,'0'
        mov [si],dl
        inc si

        cmp ecx,0
        jne .Loop

    dec si
    .LoopPrint:
        mov ah,0Eh
        mov al,[si]
        int 10h
        dec si
        cmp si,.NumberString
        jae .LoopPrint

    popad
    leave
    ret 4

    .NumberString db '0000000000'



;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;
;;  Stage 3
;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;
Stage3Start:

; Save real mode segment registers
;push gs

; Setup the three GDT entries by setting the GDT register
lgdt [GdtDesc]

; Enter protected mode
mov eax,cr0
or eax,1
mov cr0,eax

; Set segments to the data segment descriptor
mov ax,0x10
mov gs,ax

; Enter unreal mode
mov eax,cr0
and eax,0xFFFFFFFE
mov cr0,eax

; Load real mode segment registers back in.
; This will make the base of the gs segment 0x0
; while the limit will remain at 0xFFFFFFFF
;pop gs


call PrintNewLine
push MessageUnrealMode
call PrintString


LoadKernel:

; Get offset to first cluster
mov ax,0x2000		; We will load all sectors and clusters
mov es,ax			; to the address 0x20000
xor bx,bx			; Offset to load File System Definition: 0x0

; Load the File System Definition into memory
; Assumming the sector size is 512 bytes
mov ax,1			; File system definition start
mov si,3			; File system definition is 3 sectors large
mov dl,[BootDevice]
call LoadSectorsCHS

; Save the file system definition to the stack
push dword [es:0x0 + 4]		; Push cluster size (in bytes), [bp + 8]
push dword [es:0x0 + 8]		; push cluster size (in sectors), [bp + 4]
push dword [es:0x0 + 36]	; Push the offset (in sectors) to the first cluster, [bp]
mov bp,sp			; So we can access data on the stack

    xor ecx,ecx			; ecx contains cluster number, 0 is root directory
    .LoadCluster:
    push ecx				; Cluster to read
    push dword [ss:bp + 4]	; Push cluster size (in sectors)
    push dword [ss:bp]		; Push the offset (in sectors) to the first cluster
    call LoadCluster

        xor bx,bx			; bx contains directory entry number, 0 is first entry
        .DirectoryEntryLoop:
        mov al,[es:0x0 + bx]	; Move attributes byte into al
        test al,0x1				; Does directory entry exist?
        jz .SkipDirectoryEntry	; If no, than skip this entry

        ; Load filename cluster
        push dword [es:24 + bx]	; Filename cluster
        mov ax,0x1900			; After we are done using es
        mov es,ax				; Set it to the location we wish to read data to
        push dword [ss:bp + 4]	; Push cluster size (in sectors)
        push dword [ss:bp]		; Push the offset (in sectors) to the first cluster
        call LoadCluster

        ; Compare filename
        mov si,KernelFilename	; First string is ds:si
        mov di,0x0				; Second string is es:DI4
        call CompareStrings

        ; Restore es
        mov dx,0x2000
        mov es,dx

        ; Conditional jump based on the string comparasin
        cmp ax,0				; Are they different?
        je .SkipDirectoryEntry	; If yes, than skip this entry

            ; We found stage 2
            ; Load stage 2 then jump to stage 2
            mov ecx,[es:bx + 8]		; First cluster
            mov ax,0x2000			; es contains the memory location to load to
            mov es,ax
            mov edi,KernelFileLocation	; The address to copy the kernel to; this line is added; 2Mib mark
            .LoadFile:
            push ecx				; Cluster to read
            push dword [ss:bp + 4]	; Push cluster size (in sectors)
            push dword [ss:bp]		; Push the offset (in sectors) to the first cluster
            call LoadCluster

            ; This code has been added
            ; Copy cluster
            xor ebx,ebx			; Local copy mark
            .Copy:
            mov al,[es:ebx]		; The byte to copy moved into al
            mov [gs:edi],al		; Copy the byte to the destination

            inc ebx				; Increment local copy mark by one byte
            inc edi				; Increment destination mark by one byte
            cmp ebx,[bp + 8]	; Compare to cluster size in bytes
            jb .Copy			; Still more to copy? Than restart copy loop

            ; This code is not needed. We are going to load each cluster
            ; to the same address because we are copying the cluster to a
            ; new address immediatly. Therefore, overwritting the previous
            ; cluster is just fine.

            ; Increment es by the (cluster size) right shift (4)
            ; mov ax,es			; Stores es into ax
            ; mov dx,[bp + 8]		; The size of a cluster in bytes
            ; shr dx,4			; Right shift by 4 to make it a segment address
            ; add ax,dx			; Increment ax by dx
            ; mov es,ax			; Move the incremented address in ax into es

            ; Get next cluster in the cluster chain
            mov dx,es			; Save es into dx
            mov ax,0x2000		; Move 0x20000 into es
            mov es,ax			; This is our 'scratch' memory area

            xchg eax,ecx		; xchg takes up less space then mov
            call GetNextClusterInChain
            xchg eax,ecx

            mov es,dx			; Restore es

            cmp ecx,0xFFFFFFFE	; Was this cluster the last cluster?
            jne .LoadFile		; It wasn't, so load the next cluster into memory

            mov sp,bp			; Clean up the stack

            jmp EnterProtectedMode

        .SkipDirectoryEntry:
        add bx,64			; Offset to next directory entry
        cmp bx,[ss:bp + 8]	; Is offset past cluster size (in bytes)
        jl .DirectoryEntryLoop	; If no, than search next directory entry

    ; If yes, than load in next cluster chain
    xchg eax,ecx		; xchg takes up less space then mov
    call GetNextClusterInChain
    xchg eax,ecx

    ; If we are at the last cluster in the chain,
    ; than the file doesn't exist; hang the system
    cmp ecx,0xFFFFFFFE
    jne .LoadCluster

cli
hlt


; Enter protected mode
EnterProtectedMode:
mov eax,cr0
or eax,1
mov cr0,eax

; Force a far jump to load the cs segment register with our new code segment
jmp 0x08:ProtectedMode

; Compile all code from here on out as 32-bit instructions
[bits 32]
ProtectedMode:

; Set all other segments to the data segment descriptor
mov ax,0x10
mov ds,ax
mov ss,ax
mov es,ax
mov fs,ax
mov gs,ax

mov esp,0x9FB00     ; Setup the new stack


; Print a message saying that we made it into protected mode
push word 0x0001
push dword MessageProtectedMode
call PrintStringProtected


; Enable paging using a temprary virtual memory setup
Paging:
    %define PageDirectoryTable 0xA000
    %define PageTable0 0xB000
    %define PageTable768 0xC000

    ; Setup page table entries for the indentity map for the first 4MiB
    mov eax,0x3 | 0x0   ; Starting address
    mov ecx,0           ; Page table entry offset count
    .PageTable0Loop:
        mov [PageTable0 + ecx],eax
        add eax,0x1000      ; Increment the 4KiB aligned address by 1
        add ecx,4           ; Four bytes per entry
        cmp ecx,4096        ; 4096 / 4 = 1024 => all entries filled
        jl Paging.PageTable0Loop

    ; Setup page table entries for the 3GiB (plus 4MiB)
    mov eax,0x3 | 0x100000  ; Starting address
    mov ecx,0           ; Page table entry offset count
    .PageTable768Loop:
        mov [PageTable768 + ecx],eax
        add eax,0x1000      ; Increment the 4KiB aligned address by 1
        add ecx,4           ; Four bytes per entry
        cmp ecx,4096        ; 4096 / 4 = 1024 => all entries filled
        jl Paging.PageTable768Loop

    ; Clear all page directory entries first because we can not
    ; guarentee that free memory is already cleared to zeros
    mov ecx,0           ; Page directory entry offset
    .PageDirectoryClearLoop:
        mov dword [PageDirectoryTable + ecx],0  ; Write the entry to zero
        add ecx,4           ; Four bytes per entry
        cmp ecx,4096        ; 4096 / 4 = 1024 => all entries cleared
        jl Paging.PageDirectoryClearLoop

    ; Setup page directory entry 0 which identity maps the first
    ; 4MiB of memory
    mov eax,0x3 | PageTable0
    mov [PageDirectoryTable],eax

    ; Setup page directory entry 768 which will map the virtual
    ; address 3GiB (plus 4MiB) to the physical address 1MiB
    mov eax,0x3 | PageTable768
    mov [PageDirectoryTable + (768 * 4)],eax

    ; Install Page Directory
    mov eax,PageDirectoryTable  ; The physical address of the page directory table
    mov cr3,eax

    ; Enable Paging
    mov eax,cr0
    or eax,0x80000000  ; Set the 31st bit to 1 (base index 0)
    mov cr0,eax


; This code is for loading an elf32-i386 kernel
LoadElfExecutable:
    mov ax,[KernelFileLocation + 0x2C]  ; Load the number of program header table entries
    mov ebx,[KernelFileLocation + 0x1C] ; Load the offset from the begining of the file to the program header
    add ebx,KernelFileLocation          ; Add the base of the file image to get the absolute position of the first entry in the program header table
    xor edx,edx                         ; Clear the upper bits of edx
    mov dx,[KernelFileLocation + 0x2A]  ; Load the size of each program header table entry

    .ProgramHeaderLoop:
        mov esi,[ebx + 0x4]             ; Load the offset into the file of the start of the current segment
        add esi,KernelFileLocation      ; Add the base of the file image to the offset from above to get the absolute position of the current segment

        mov edi,[ebx + 0x8]             ; Load the position in virtual memory where we are supposed to load this segment
        sub edi,0xC0000000              ; Subtract 3GiB from the actual address. This is because 1MiB of memory is mapped to the 3GiB part.
        add edi,KernelLocation          ; Add 1MiB

        mov ecx,[ebx + 0x10]            ; Load the size of the current segment in the file image

        cld                             ; We want to increment esi and edi
        rep movsb                       ; Copy the segment from the file to memory

        .SkipCopy:

        add ebx,edx                     ; Add the size of one program header entry to get the position of the next header
        dec ax                          ; Decrement the program header table entry count
        cmp ax,0                        ; If ax is 0 we are out of entries to do
        jne LoadElfExecutable.ProgramHeaderLoop

    mov ebp,[KernelFileLocation + 0x18] ; Load the entry point address
    jmp ebp                             ; We use ebp so the stack is setup correctly

; Just incase the kernel returns execution back
cli
hlt



;;;;;;;;;;;;;;;;;
;;  PrintStringProtected
;;
;;  Arguments:
;;  dword PointerToString
;;	word (low byte) Attribute
;;
;;  Returns:
;;  None
;;;;;;;;;;;;;;;;;
PrintStringProtected:
enter 0,0
push eax
push ebx
push esi

xor ebx,ebx
mov esi,[ebp + 8]
mov ah,[ebp + 12]

.Loop:
mov al,[esi]
cmp al,0
je .Exit

mov byte [0xB8000 + ebx],al
mov byte [0xB8000 + ebx + 1],ah
inc esi
add ebx,2

jmp .Loop
    
.Exit:

pop esi
pop ebx
pop eax
leave
ret 4


;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;
;;  Stage 2 and Stage 3 Data
;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;
KernelFilename              db 'Kernel.elf',0

MessageGeometrySectors      db 'Sectors: ',0
MessageGeometryHeads        db 'Heads: ',0
MessageGeometryCylinders    db 'Cylinders: ',0

MessageA20Enabled           db 'A20 Line is enabled',13,10,0
MessageA20Disabled          db 'A20 Line is disabled',13,10,0
MessageA20Failed            db 'A20 Line failed to enable. Halting',13,10,0

MessageTotalSystemMemory    db 'Total System Memory (KiB): ',0
MessageMemoryMap			db 'Memory map entry count: ',0

MessageVesaSupported		db 'Vesa is supported',13,10,0
MessageVesaNotSupported		db 'Vesa is not supported',13,10,0

MessageUnrealMode			db 'Entered Unreal Mode',0
MessageKernelLoaded         db 'Kernel Loaded',0
MessageProtectedMode		db 'Entered Protected Mode',0


Gdt:

    GdtNull:
        dd 0
        dd 0

    GdtCode:
        dw 0xFFFF           ; Limit
        dw 0x0              ; Base address

        db 0x0              ; Continued base address
        db 10011010b        ; Type, privilage, ring level
        db 11001111b        ; Continued limit, attributes, granularity
        db 0x0              ; Continued base address

    GdtData:
        dw 0xFFFF           ; Limit
        dw 0x0              ; Base address

        db 0x0              ; Continued base address
        db 10010010b        ; Type, privilage, ring level
        db 11001111b        ; Continued limit, attributes, granularity
        db 0x0              ; Continued base address

    GdtEnd:

GdtDesc:
    dw GdtEnd - Gdt - 1
    dd Gdt


; Round the size of the complete boot sector to a 512 byte multiple
times ($ - $$) + (512 - (($ - $$) % 512)) - ($ - $$) db 0





;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;
;;  Memory Persistent Variables
;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;
[absolute 0x500]
BootDevice                  resb 1

DiskGeometry:
.SectorCount                resb 1  ; Low 6 bits only
.HeadCount                  resb 1
.CylinderCount              resw 1  ; Low 10 bits only
.DriveCount                 resb 1





;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;
;;  Memory Map
;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;

; Address               Size    Description

; 0x500                 1h      Boot Device
; 0x501                 1h      Sector Count of Boot Device
; 0x502                 1h      Head Count of Boot Device
; 0x503                 2h      Cylinder Count of Boot Device
; 0x505                 1h      Drive Count