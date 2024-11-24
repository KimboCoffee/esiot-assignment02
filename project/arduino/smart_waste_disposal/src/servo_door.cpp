#include <Arduino.h>
#include "servo_door.h"

#define OPEN_FOR_INSERTION 2250
#define CLOSED 1500
#define OPEN_FOR_EMPTYING 750

ServoDoor::ServoDoor(int pin) {
    this->motor = new ServoTimer2();
    this->pin = pin;
}

void ServoDoor::openForInsertion() {
    this->set(OPEN_FOR_INSERTION);
}

void ServoDoor::close() {
    this->set(CLOSED);
}

void ServoDoor::openForEmptying() {
    this->set(OPEN_FOR_EMPTYING);
}

void ServoDoor::set(int value) {
    this->motor->attach(this->pin);
    this->motor->write(value);
}