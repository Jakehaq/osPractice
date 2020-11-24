#include "subsections/kernelFuncs/printText.cpp"


extern const char Test[];

extern "C" void _start() {
    clearSreen(FOREGROUND_WHITE | BACKGROUND_BLACK);
    setCursorPosition(positionFromCoords(0, 0));
    printString("Welcome\n\rto elephantOS\n\r", BACKGROUND_BLACK | FOREGROUND_LIGHTRED);
    printString(hexToString(0x1234abcd));
    printString(Test);
    return;
}