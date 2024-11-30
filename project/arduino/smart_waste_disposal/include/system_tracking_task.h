#ifndef __SYSTEM_TRACKING_TASK__
#define __SYSTEM_TRACKING_TASK__

#include "task.h"

class SystemTrackingTask: public Task {
    public:
        void step(long schedPeriod);
};

#endif