#ifndef __TASK__
#define __TASK__

class Task {
    public:
        virtual void step(int schedPeriod) = 0;
};

#endif