print:
    pusha ;puts stuff on the stack to save it

    printLoop:
        mov al, [si] ;moves current character into working register
        cmp al, 0x00 ;checks to see the current character is 0 (aka the end)
        jne charPrint ;if it's not, it goes to print that character
        popa ;takes stuff off the stack
        ret ;ends the function

    charPrint:
        mov ah, 0x0e ;puts it into print mode
        int 0x10 ;prints to screen
        add si, 1 ;increments source index to point to next character
        jmp printLoop ;goes back to beginning