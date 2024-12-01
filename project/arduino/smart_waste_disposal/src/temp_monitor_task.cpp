#include <Arduino.h>
#include "temp_monitor_task.h"
#include "temperature_sensor_impl.h"

#define TEMP_SENSOR A0

TempMonitorTask::TempMonitorTask(int period, SystemStateTracker *systemTracker) {
    this->period = period;
    this->schedSteps = 0;
    this->setState(OK);
    this->alertSteps = 0;
    this->sensor = new TemperatureSensorImpl(TEMP_SENSOR);
    this->lastMeasure = sensor->getTemp();
    this->systemTracker = systemTracker;
}

void TempMonitorTask::step(int schedPeriod) {
    if (this->schedSteps * schedPeriod >= this->period) {
        this->schedSteps = 0;
        this->lastMeasure = sensor->getTemp();
        
        if (state != NOT_OK) {
            if (this->lastMeasure > TEMP_THRESHOLD) {
                if (this->state == OK) {
                    this->setState(ALERT);
                } else if (this->state == ALERT) {
                    this->alertSteps++;
                    if (this->alertSteps * this->period >= ALERT_TIME_THRESHOLD) {
                        this->setState(NOT_OK);
                    }
                }
            } else if (this->state == ALERT) {
                this->setState(OK);
            }
        }
    } else {
        this->schedSteps++;
    }
}

float TempMonitorTask::getLastMeasure() {
    return this->lastMeasure;
}

void TempMonitorTask::setState(TempMonitorState state) {
    switch (state) {
        case OK:
            this->systemTracker->restoreSystem(TEMP_MONITOR);
            break;

        case NOT_OK:
            this->systemTracker->blockSystem(TEMP_MONITOR);
            break;
            
        case ALERT:
            this->alertSteps = 0;
            break;
    }
    this->state = state;
}
