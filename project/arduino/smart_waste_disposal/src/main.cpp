#include <Arduino.h>
#include "temperature_sensor_impl.h"
#include "led.h"
#include "button_impl.h"
#include "lcd_screen.h"
#include "pir_user_detector.h"
#include "servo_door.h"
#include "timer_impl.h"
#include "sonar_level_gauge.h"
#include "coop_r_r_scheduler.h"
#include "temp_monitor_task.h"
#include "level_monitor_task.h"
#include "system_state_tracker.h"

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

SystemStateTracker *systemTracker;
LevelMonitorTask *levelMonitor;
Scheduler *scheduler;
int period;

void setup() {
    Serial.begin(9600);
    period = 500;
    scheduler = new CoopRRScheduler(period);
    systemTracker = new SystemStateTracker();
    levelMonitor = new LevelMonitorTask(5 * period, systemTracker);
    scheduler->bind(levelMonitor);
}

void loop() {
    scheduler->schedule();
    Serial.print("Filling level: ");
    Serial.println(levelMonitor->getLastMeasure());
    if (systemTracker->isSystemBlocked()) {
        Serial.println("The system is blocked");
    }
}