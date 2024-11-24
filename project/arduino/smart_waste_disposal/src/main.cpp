#include <Arduino.h>
#include "temperature_sensor_impl.h"
#include "led.h"
#include "button_impl.h"
#include "lcd_screen.h"
#include "pir_user_detector.h"

#define TEMP_SENSOR A0
#define GREEN_LED 12
#define RED_LED 13
#define OPEN_BUTTON 11
#define CLOSE_BUTTON 10
#define USER_DETECTOR 2
#define LCD_ADDRESS 0x27
#define LCD_ROWS 4
#define LCD_COLS 20

UserDetector *detector;

void setup() {
  Serial.begin(9600);
  detector = new PIRUserDetector(USER_DETECTOR);
  delay(10000);
  Serial.println("Calibration done");
}

void loop() {
  if (detector->isDetecting()) {
    Serial.println("User detected");
  }
  delay(500);
}