#pragma once
#define VGA_MEMORY (unsigned char*) 0xb8000
#define VGA_WIDTH 80
#include "io.c"
#include "typeDef.c"

u_int16 cursorPosition;

void setCursorPosition(u_int16 position) {
    outb(0x3d4, 0x0f);
    outb(0x3d5, (u_int8)(position & 0xff));
    outb(0x3d4, 0x0e);
    outb(0x3d5, (u_int8)((position >> 8) & 0xff));

    cursorPosition = position;
}

u_int16 positionFromCoords(u_int8 x, u_int8 y) {
    return y * VGA_WIDTH + x;
}

void printString(const char* str) {
    u_int8* pointr = (u_int8*)str;
    u_int16 index = cursorPosition;

    while (*pointr != 0) {
        *(VGA_MEMORY + index*2) = *pointr;
        pointr++;
        index++;
    }
    setCursorPosition(index);
}