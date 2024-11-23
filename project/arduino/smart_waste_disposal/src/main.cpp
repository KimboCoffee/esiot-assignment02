#include <Arduino.h>
#include "temperature_sensor_impl.h"
#include "led.h"
#include "button_impl.h"

#define TEMP_SENSOR A0
#define GREEN_LED 12
#define RED_LED 13
#define OPEN_BUTTON 11
#define CLOSE_BUTTON 10

Button *openButton;
Button *closeButton;

void setup() {
  openButton = new ButtonImpl(OPEN_BUTTON);
  closeButton = new ButtonImpl(CLOSE_BUTTON);
  Serial.begin(9600);
}

void loop() {
  if (openButton->isPressed()) Serial.println("Open pressed");
  if (closeButton->isPressed()) Serial.println("Close pressed");
}