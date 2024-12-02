#include <Arduino.h>
#include "led.h"

#define OFF 0
#define ON 1

Led::Led(int pin) {
    this->pin = pin;
    this->state = OFF;
    pinMode(this->pin, OUTPUT);
}

void Led::turnOn() {
    this->state = ON;
    digitalWrite(this->pin, this->state);
}

void Led::turnOff() {
    this->state = OFF;
    digitalWrite(this->pin, this->state);
}

bool Led::isOn() {
    return this->state;
}