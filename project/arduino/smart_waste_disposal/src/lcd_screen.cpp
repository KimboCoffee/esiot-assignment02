#include "lcd_screen.h"

LCDScreen::LCDScreen(int address, int rows, int cols) {
    this->lcd = new LiquidCrystal_I2C(address, rows, cols);
    this->lcd->init();
}

void LCDScreen::turnOn() {
    this->lcd->backlight();
}

void LCDScreen::turnOff() {
    this->lcd->clear();
    this->lcd->noBacklight();
}

void LCDScreen::clear() {
    this->lcd->clear();
}

void LCDScreen::println(int row, String msg) {
    this->lcd->setCursor(0, row);
    this->lcd->print(msg);
}