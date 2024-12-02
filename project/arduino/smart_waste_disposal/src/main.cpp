#include <Arduino.h>
#include "coop_r_r_scheduler.h"
#include "temp_monitor_task.h"
#include "level_monitor_task.h"
#include "system_state_tracker.h"
#include "communication_task.h"
#include "container_handler_task.h"

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