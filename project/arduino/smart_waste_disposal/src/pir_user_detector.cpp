#include <Arduino.h>
#include "pir_user_detector.h"

PIRUserDetector::PIRUserDetector(int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

bool PIRUserDetector::isDetecting() {
    return digitalRead(this->pin);
}