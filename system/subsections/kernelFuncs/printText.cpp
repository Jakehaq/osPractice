#pragma once
#define VGA_MEMORY (unsigned char*) 0xb8000
#define VGA_WIDTH 80
#include "io.cpp"
#include "typeDef.cpp"
#include "textModeColorCodes.cpp"

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

void printString(const char* str, u_int8 color = BACKGROUND_BLACK | FOREGROUND_WHITE) {
    u_int8* pointr = (u_int8*)str;
    u_int16 index = cursorPosition;

    while (*pointr != 0) {
        
        switch (*pointr)
        {
        case 10:
            index += VGA_WIDTH;
            break;
        case 13:
            index -= index % VGA_WIDTH;
            break;
        default:
            *(VGA_MEMORY + index*2) = *pointr;
            *(VGA_MEMORY + index*2 + 1) = color;
            
            index++;
        }
        pointr++;
    }
    setCursorPosition(index);
}

void clearSreen(u_int64 clearColor = BACKGROUND_BLACK | FOREGROUND_WHITE) {
    u_int64 value = 0;
    value += clearColor << 8;
    value += clearColor << 24;
    value += clearColor << 40;
    value += clearColor << 56;
    for (u_int64* i = (u_int64*)VGA_MEMORY; i < (u_int64*)(VGA_MEMORY + 4000); i++) {
        *i = value;
    }
}

char hexToStringOutput[128];

template<typename T>
const char* hexToString(T value) {
    T* valPtr = &value;
    u_int8* ptr;
    u_int8 temp;
    u_int8 size = (sizeof(T)) * 2 - 1;
    u_int8 i;
    for (i = 0; i < size; i++) {
        ptr = ((u_int8*)valPtr + i);
        temp = ((*ptr & 0xF0) >> 4);
        hexToStringOutput[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
        temp = ((*ptr & 0x0F));
        hexToStringOutput[size - (i * 2 + 0)] = temp + (temp > 9 ? 55 : 48);
    }
    hexToStringOutput[size + 1] = 0;
    return hexToStringOutput;
}
