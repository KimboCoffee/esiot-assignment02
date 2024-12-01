#ifndef __COMMUNICATION_TASK__
#define __COMMUNICATION_TASK__

#include "task.h"
#include "system_state_tracker.h"
#include "temp_monitor_task.h"
#include "level_monitor_task.h"

#define BAUD_RATE 9600

class CommunicationTask: public Task {
    public:
        CommunicationTask(int period, SystemStateTracker *systemTracker,
            TempMonitorTask *tempMonitor, LevelMonitorTask *levelMonitor);
        void step(int schedPeriod);

    private:
        SystemStateTracker *systemTracker;
        TempMonitorTask *tempMonitor;
        LevelMonitorTask *levelMonitor;
        int period;
        int schedSteps;
};

#endif