#include "level_monitor_task.h"
#include "sonar_level_gauge.h"

#define LEVEL_ECHO 8
#define LEVEL_TRIG 7
#define LEVEL_THRESHOLD 98.0

LevelMonitorTask::LevelMonitorTask(int period, SystemStateTracker *systemTracker) {
    this->period = period;
    this->systemTracker = systemTracker;
    this->sensor = new SonarLevelGauge(LEVEL_TRIG, LEVEL_ECHO);
    this->schedSteps = 0;
    this->measure();
    this->state = LEVEL_MONITOR_OK;
}

void LevelMonitorTask::step(int schedPeriod) {
    if (this->schedSteps * schedPeriod >= this->period) {
        this->measure();
        if (this->state == LEVEL_MONITOR_OK && this->lastMeasure > LEVEL_THRESHOLD) {
            this->setState(LEVEL_MONITOR_NOT_OK);
        }
    }
    this->schedSteps++;
}

void LevelMonitorTask::setState(LevelMonitorState state) {
    switch(state) {
        case LEVEL_MONITOR_OK:
            systemTracker->restoreSystem(LEVEL_MONITOR);
            break;

        case LEVEL_MONITOR_NOT_OK:
            systemTracker->blockSystem(LEVEL_MONITOR);
            break;
    }
    this->state = state;
}

void LevelMonitorTask::measure() {
    this->lastMeasure = sensor->getFillingPercentage();
    this->systemTracker->setLevel(this->lastMeasure);
}
