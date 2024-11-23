#include <Arduino.h>
#include "temperature_sensor_impl.h"
#include "led.h"

#define TEMP_SENS A0
#define GREEN_LED 12
#define RED_LED 13

Light *green;
Light *red;

void setup() {
  red = new Led(RED_LED);
  green = new Led(GREEN_LED);
  Serial.begin(9600);
}

void loop() {
  red->turn();
  delay(500);
  red->turn();
  green->turn();
  delay(500);
  green->turn();
}