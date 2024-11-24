#include <Arduino.h>
#include "servo_door.h"

#define OPEN_FOR_INSERTION 2250
#define CLOSED 1500
#define OPEN_FOR_EMPTYING 750

ServoDoor::ServoDoor(int pin) {
    this->motor = new ServoTimer2();
    this->pin = pin;
}

void ServoDoor::lock() {
    this->motor->detach();
}

void ServoDoor::unlock() {
    this->motor->attach(this->pin);
}

void ServoDoor::openForInsertion() {
    this->motor->write(OPEN_FOR_INSERTION);
}

void ServoDoor::close() {
    this->motor->write(CLOSED);
}

void ServoDoor::openForEmptying() {
    this->motor->write(OPEN_FOR_EMPTYING);
}