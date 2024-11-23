#include <Arduino.h>
#include "button_impl.h"

#define DEBOUNCE_TIME 30

ButtonImpl::ButtonImpl(int pin) {
    this->pin = pin;
    this->prev_pressing = millis();
}

bool ButtonImpl::isPressed() {
    int now = millis();
    if (digitalRead(this->pin) && (now - this->prev_pressing) > DEBOUNCE_TIME) {
        this->prev_pressing = now;
        return true;
    } else return false;
}