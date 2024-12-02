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
    pinMode(this->pin, HIGH);
}

void Led::turnOff() {
    this->state = OFF;
    pinMode(this->pin, LOW);
}

bool Led::isOn() {
    return this->state;
}