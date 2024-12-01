#include <Arduino.h>
#include "temp_monitor_task.h"
#include "temperature_sensor_impl.h"

#define TEMP_SENSOR A0

TempMonitorTask::TempMonitorTask(int period, SystemStateTracker *systemTracker) {
    this->period = period;
    this->schedSteps = 0;
    this->setState(TEMP_MONITOR_OK);
    this->alertSteps = 0;
    this->sensor = new TemperatureSensorImpl(TEMP_SENSOR);
    this->measure();
    this->systemTracker = systemTracker;
}

void TempMonitorTask::step(int schedPeriod) {
    if (this->schedSteps * schedPeriod >= this->period) {
        this->schedSteps = 0;
        this->measure();
        
        if (state != TEMP_MONITOR_NOT_OK) {
            if (this->lastMeasure > TEMP_THRESHOLD) {
                if (this->state == TEMP_MONITOR_OK) {
                    this->setState(TEMP_MONITOR_ALERT);
                } else if (this->state == TEMP_MONITOR_ALERT) {
                    this->alertSteps++;
                    if (this->alertSteps * this->period >= ALERT_TIME_THRESHOLD) {
                        this->setState(TEMP_MONITOR_NOT_OK);
                    }
                }
            } else if (this->state == TEMP_MONITOR_ALERT) {
                this->setState(TEMP_MONITOR_OK);
            }
        }
    }
    this->schedSteps++;
}

void TempMonitorTask::setState(TempMonitorState state) {
    switch (state) {
        case TEMP_MONITOR_OK:
            this->systemTracker->restoreSystem(TEMP_MONITOR);
            break;

        case TEMP_MONITOR_NOT_OK:
            this->systemTracker->blockSystem(TEMP_MONITOR);
            break;
            
        case TEMP_MONITOR_ALERT:
            this->alertSteps = 0;
            break;
    }
    this->state = state;
}

void TempMonitorTask::measure() {
    this->lastMeasure = this->sensor->getTemp();
    this->systemTracker->setTemp(this->lastMeasure);
}
