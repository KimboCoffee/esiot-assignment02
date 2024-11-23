#include <Arduino.h>
#include "temperature_sensor_impl.h"
#include "led.h"
#include "button_impl.h"
#include "lcd_screen.h"

#define TEMP_SENSOR A0
#define GREEN_LED 12
#define RED_LED 13
#define OPEN_BUTTON 11
#define CLOSE_BUTTON 10
#define LCD_ADDRESS 0x27
#define LCD_ROWS 4
#define LCD_COLS 20

Screen *screen;
int i;

void setup() {
  screen = new LCDScreen(LCD_ADDRESS, LCD_ROWS, LCD_COLS);
  screen->turnOn();
  i = 0;
}

void loop() {
  i = (i + 1) % LCD_ROWS;
  screen->println(i, "Hello World!");
}