#include <Arduino.h>
#include "temperature_sensor_impl.h"
#include "led.h"
#include "button_impl.h"
#include "lcd_screen.h"
#include "pir_user_detector.h"
#include "servo_door.h"
#include "timer_impl.h"

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
#define USER_DETECTOR 2

/*LCD settings*/
#define LCD_ADDRESS 0x27
#define LCD_ROWS 4
#define LCD_COLS 20

Door *door;
TimerImpl* timer;

void setup() {
  door = new ServoDoor(DOOR);
  timer = new TimerImpl(1000);
}

void loop() {
  door->unlock();
  door->openForInsertion();
  timer->waitForNextTick();
  door->close();
  timer->waitForNextTick();
  door->openForEmptying();
  timer->waitForNextTick();
  door->lock();
}