#include <Arduino.h>
#include "coop_r_r_scheduler.h"
#include "temp_monitor_task.h"
#include "level_monitor_task.h"
#include "system_state_tracker.h"
#include "communication_task.h"
#include "container_handler_task.h"

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
TempMonitorTask *tempMonitor;
CommunicationTask *commTask;
ContainerHandlerTask *containerHandler;
Scheduler *scheduler;
int period;

void setup() {
    period = 100;
    scheduler = new CoopRRScheduler(period);
    systemTracker = new SystemStateTracker();
    levelMonitor = new LevelMonitorTask(10 * period, systemTracker);
    tempMonitor = new TempMonitorTask(10 * period, systemTracker);
    commTask = new CommunicationTask(5 * period, systemTracker, tempMonitor, levelMonitor);
    containerHandler = new ContainerHandlerTask(period, systemTracker);
    scheduler->bind(levelMonitor);
    scheduler->bind(tempMonitor);
    scheduler->bind(commTask);
    scheduler->bind(containerHandler);
}

void loop() {
    scheduler->schedule();
}