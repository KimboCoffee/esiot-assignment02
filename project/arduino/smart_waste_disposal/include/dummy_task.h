#ifndef __DUMMY_TASK__
#define __DUMMY_TASK__

#include "task.h"

class DummyTask : public Task {
    public:
        DummyTask(long period);
        void step(long schedPeriod);

    private:
        long period;
        int stepCount;
};

#endif