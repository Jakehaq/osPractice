[org 0x7c00]

section .text
    global main

main:
    cli
    jmp 0x0000:ZeroSeg

ZeroSeg:
    xor ax, ax
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov sp, main
    cld
    sti

    push ax
    xor ax, ax
    int 0x13
    pop ax


Bootload:
    mov al, 8 ;number of sectors to read, increase as initial file gets bigger, 512 bytes each
    mov cl, 2
    call readDisk
    jmp PROGRAM_SPACE

%include "subsections/sector.asm"
%include "subsections/print.asm"

times 510 - ($-$$) db 0
    dw 0xAA55


