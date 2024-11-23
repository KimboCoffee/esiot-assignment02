#include <Arduino.h>
#include "temperature_sensor_impl.h"

TemperatureSensor *tempSensor;

void setup() {
  tempSensor = new TemperatureSensorImpl(A0);
  Serial.begin(9600);
}

void loop() {
  Serial.println(tempSensor->getTemp());
  delay(1000);
}