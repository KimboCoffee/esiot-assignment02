#include <Arduino.h>
#include "temperature_sensor_impl.h"
#include "led.h"
#include "button_impl.h"
#include "lcd_screen.h"
#include "pir_user_detector.h"
#include "servo_door.h"
#include "timer_impl.h"
#include "sonar_level_gauge.h"
#include "dummy_task.h"

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

DummyTask *t1;
DummyTask *t2;
TimerImpl *timer;
int period;

void setup() {
  Serial.begin(9600);
  period = 100;
  t1 = new DummyTask(10 * period);
  t2 = new DummyTask(20 * period);
  timer = new TimerImpl(period);
}

void loop() {
  timer->waitForNextTick();
  t1->step(period);
  t2->step(period);
}