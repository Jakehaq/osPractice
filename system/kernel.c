#include "subsections/kernelFuncs/printText.c"
void _start() {
    setCursorPosition(positionFromCoords(0, 0));
    printString("Hello world");
    return;
}