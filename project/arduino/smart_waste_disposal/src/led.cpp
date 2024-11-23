#include "led.h"

#define OFF 0
#define ON 1

Led::Led(int pin) {
    this->pin = pin;
    this->state = OFF;
    pinMode(pin, OUTPUT);
}

void Led::turn() {
    this->state = !this->state;
    digitalWrite(this->pin, this->state);
}

bool Led::isOn() {
    return this->state;
}