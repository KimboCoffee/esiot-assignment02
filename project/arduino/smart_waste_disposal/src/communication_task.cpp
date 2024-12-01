#include <Arduino.h>
#include "communication_task.h"

CommunicationTask::CommunicationTask(int period, SystemStateTracker *systemTracker,
    TempMonitorTask *tempMonitor, LevelMonitorTask *levelMonitor) {
        this->period = period;
        this->schedSteps = 0;
        this->systemTracker = systemTracker;
        this->tempMonitor = tempMonitor;
        this->levelMonitor = levelMonitor;
        Serial.begin(BAUD_RATE);
}

void CommunicationTask::step(int schedPeriod) {
    if (this->schedSteps * schedPeriod >= period) {
        this->schedSteps = 0;
        
        if (Serial.available()) {
            char msg = Serial.read();
            if (msg == '1') {
                this->systemTracker->restoreSystem(TEMP_MONITOR);
                this->tempMonitor->setState(TEMP_MONITOR_OK);
            } else if (msg == '2') {
                this->systemTracker->restoreSystem(LEVEL_MONITOR);
                this->levelMonitor->setState(LEVEL_MONITOR_OK);
            }
        }

        Serial.println(this->period);
        Serial.println(this->systemTracker->getTemp());
        Serial.println(this->systemTracker->isTempExceeded() ? 1 : 0);
        Serial.println(this->systemTracker->getLevel());
        Serial.println(this->systemTracker->isLevelExceeded() ? 1 : 0);
    }
    this->schedSteps++;
}
