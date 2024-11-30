#ifndef __TEMP_MONITOR_TASK__
#define __TEMP_MONITOR_TASK__

#include "task.h"

class TempMonitorTask: public Task {
    public:
        void step(int schedPeriod);
};

#endif