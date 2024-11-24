#ifndef __LCD_SCREEN__
#define __LCD_SCREEN__

#include <LiquidCrystal_I2C.h>
#include "screen.h"

class LCDScreen : public Screen {
    public:
        LCDScreen(int address, int rows, int cols);
        void turnOn();
        void turnOff();
        void println(int row, char* msg);

    private:
        LiquidCrystal_I2C *lcd;
};

#endif