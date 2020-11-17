[bits 16]
enterProtectedMode:
    mov al, 'h'
    mov ah, 0x0e
    int 0x10
    call enableA20
    cli
    lgdt [gdtDescriptor]

    mov eax, cr0
    or al, 1
    mov cr0, eax
    jmp codeseg:startProtectedMode

enableA20:
    in al, 0x02
    or al, 2
    out 0x92, al
    ret

%include "subsections/gdt.asm"


[bits 32]

%include "subsections/cpuID.asm"
%include "subsections/paging.asm"

startProtectedMode:
    mov ax, dataseg
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax




    call detectCPUID
    call detectLongMode

    call setUpPaging
    call editGDT
    
    jmp codeseg:start64Bit

[bits 64]
[extern _start]
start64Bit:
    mov edi, 0xb8000
    mov rax, 0x1f201f201f201f20
    mov ecx, 500
    rep stosq
    call _start
    jmp $

;times 4096 - ($-$$) db 0 ;make sure to pad file so it corresponds with size of read