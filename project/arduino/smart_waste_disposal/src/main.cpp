#include <Arduino.h>
#include "coop_r_r_scheduler.h"
#include "temp_monitor_task.h"
#include "level_monitor_task.h"
#include "system_state_tracker.h"
#include "communication_task.h"
#include "container_handler_task.h"

#define SCHED_PERIOD 50
#define LEVEL_MONITOR_PERIOD 200
#define TEMP_MONITOR_PERIOD 200
#define COMM_TASK_PERIOD 200
#define CONTAINER_HANDLER_PERIOD 50

SystemStateTracker *systemTracker;
LevelMonitorTask *levelMonitor;
TempMonitorTask *tempMonitor;
CommunicationTask *commTask;
ContainerHandlerTask *containerHandler;
Scheduler *scheduler;
int period;

void setup() {
    period = 100;
    scheduler = new CoopRRScheduler(SCHED_PERIOD);
    systemTracker = new SystemStateTracker();
    levelMonitor = new LevelMonitorTask(LEVEL_MONITOR_PERIOD, systemTracker);
    tempMonitor = new TempMonitorTask(TEMP_MONITOR_PERIOD, systemTracker);
    commTask = new CommunicationTask(COMM_TASK_PERIOD, systemTracker, tempMonitor, levelMonitor);
    containerHandler = new ContainerHandlerTask(CONTAINER_HANDLER_PERIOD, systemTracker);
    scheduler->bind(levelMonitor);
    scheduler->bind(tempMonitor);
    scheduler->bind(commTask);
    scheduler->bind(containerHandler);
}

void loop() {
    scheduler->schedule();
}