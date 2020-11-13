PROGRAM_SPACE equ 0x8000

readDisk:
    pusha
    mov ah, 0x02
    mov dl, 0x80
    mov ch, 0
    mov dh, 0

    push bx
    mov bx, 0
    mov es, bx
    pop bx
    mov bx, PROGRAM_SPACE

    int 0x13
    jc diskError

    popa
    ret

diskError:

    jmp $
