#include "subsections/kernelFuncs/printText.cpp"
extern "C" void _start() {
    setCursorPosition(positionFromCoords(0, 0));
    printString("Hello world\n\rGiorno");
    return;
}