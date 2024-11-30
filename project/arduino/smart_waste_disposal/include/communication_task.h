#ifndef __COMMUNICATION_TASK__
#define __COMMUNICATION_TASK__

#include "task.h"

class CommunicationTask: public Task {
    public:
        void step(long schedPeriod);
};

#endif