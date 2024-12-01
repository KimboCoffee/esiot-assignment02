#include "system_state_tracker.h"

SystemStateTracker::SystemStateTracker(){
    this->tempState = TEMP_FINE;
    this->levelState = LEVEL_FINE;
}

void SystemStateTracker::restoreSystem(ExceptionSource restoredMonitor) {
    if (restoredMonitor == TEMP_MONITOR) {
        this->tempState = TEMP_FINE;
    } else {
        this->levelState = LEVEL_FINE;
    }
}

void SystemStateTracker::blockSystem(ExceptionSource exceededMonitor) {
    if (exceededMonitor == TEMP_MONITOR) {
        this->tempState = TEMP_EXCEEDED;
    } else {
        this->levelState = LEVEL_EXCEEDED;
    }
}

bool SystemStateTracker::isTempExceeded() {
    return this->tempState == TEMP_EXCEEDED;
}

bool SystemStateTracker::isLevelExceeded() {
    return this->levelState == LEVEL_EXCEEDED;
}