#include <Arduino.h>
#include "temperature_sensor_impl.h"

/**
 * known because TMP36 scale starts from -500mV
 */
#define OFFSET (-0.500)
/**
 * known because TMP36 sensitivity is 10mV/°C
 */
#define FACTOR 100

TemperatureSensorImpl::TemperatureSensorImpl(int pin) {
    this->pin = pin;
}

float TemperatureSensorImpl::getTemp() {
    float voltage = (float)analogRead(this->pin) / 1024 * 5;
    return (voltage + OFFSET) * FACTOR;
}