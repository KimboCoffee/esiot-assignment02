#include "servo_door.h"

#define OPEN_FOR_INSERTION 180
#define CLOSED 90
#define OPEN_FOR_EMPTYING 0

ServoDoor::ServoDoor(int pin) {
    this->motor = new Servo();
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