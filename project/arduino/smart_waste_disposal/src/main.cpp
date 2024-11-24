#include <Arduino.h>
#include "temperature_sensor_impl.h"
#include "led.h"
#include "button_impl.h"
#include "lcd_screen.h"
#include "pir_user_detector.h"
#include "servo_door.h"
#include "timer_impl.h"
#include "sonar_level_gauge.h"

/*analog pins*/
#define TEMP_SENSOR A0
#define LCD_SDA A4
#define LCD_SCL A5

/*digital pins*/
#define GREEN_LED 12
#define RED_LED 13
#define OPEN_BUTTON 11
#define CLOSE_BUTTON 10
#define DOOR 9
#define LEVEL_ECHO 8
#define LEVEL_TRIG 7
#define USER_DETECTOR 2

/*LCD settings*/
#define LCD_ADDRESS 0x27
#define LCD_ROWS 4
#define LCD_COLS 20

SonarLevelGauge *levelGauge;

void setup() {
  Serial.begin(9600);
  levelGauge = new SonarLevelGauge(LEVEL_TRIG, LEVEL_ECHO);
}

void loop() {
  Serial.print("Filling percentage: ");
  Serial.println(levelGauge->getFillingPercentage());
  delay(1000);
}