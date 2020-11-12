gdtNullDesc:
    dd 0
    dd 0

gdtCodeDesc:
    dw 0xffff
    dw 0x0000
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00

gdtDataDesc:
    dw 0xffff
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00
gdtEnd:

gdtDescriptor:
    gdtSize: 
        dw gdtEnd - gdtNullDesc - 1
        dd gdtNullDesc

codeseg equ gdtCodeDesc - gdtNullDesc
dataseg equ gdtDataDesc - gdtNullDesc

[bits 32]
editGDT:
    mov [gdtCodeDesc + 6], byte 10101111b
    mov [gdtDataDesc + 6], byte 10101111b
    ret

[bits 16]