#include <Arduino.h>
#include "temperature_sensor_impl.h"

#define BASE_VALUE (-40)
#define SENSITIVITY 0.01

TemperatureSensorImpl::TemperatureSensorImpl(int pin) {
    this->pin = pin;
}

float TemperatureSensorImpl::getTemp() {
    float voltage = (float)analogRead(this->pin) / 1024 * 5;
    return BASE_VALUE + (voltage / SENSITIVITY);
}