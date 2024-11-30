#ifndef __CONTAINER_HANDLER_TASK__
#define __CONTAINER_HANDLER_TASK__

#include "task.h"

class ContainerHandlerTask: public Task {
    public:
        void step(long schedPeriod);
};

#endif