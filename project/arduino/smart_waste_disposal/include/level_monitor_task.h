#ifndef __LEVEL_MONITOR_TASK__
#define __LEVEL_MONITOR_TASK__

#include "task.h"
#include "system_state_tracker.h"
#include "level_gauge.h"

typedef enum {
    LEVEL_MONITOR_OK,
    LEVEL_MONITOR_NOT_OK
} LevelMonitorState;

class LevelMonitorTask: public Task {
    public:
        LevelMonitorTask(int period, SystemStateTracker *systemTracker);
        void step(int schedPeriod);
        float getLastMeasure();
        void setState(LevelMonitorState state);

    private:
        int period;
        SystemStateTracker *systemTracker;
        LevelGauge *levelGauge;
        float lastMeasure;
        int schedSteps;
        LevelMonitorState state;
};

#endif