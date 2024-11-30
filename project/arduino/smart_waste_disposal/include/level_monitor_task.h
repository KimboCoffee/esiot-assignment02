#ifndef __LEVEL_MONITOR_TASK__
#define __LEVEL_MONITOR_TASK__

#include "task.h"

class LevelMonitorTask: public Task {
    public:
        void step(long schedPeriod);
};

#endif