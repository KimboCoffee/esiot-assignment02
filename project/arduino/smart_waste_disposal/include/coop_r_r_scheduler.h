#ifndef __COOP_R_R_SCHEDULER__
#define __COOP_R_R_SCHEDULER__

#include "timer_impl.h"
#include "scheduler.h"

#define MAX_OCCUPATION 5

class CoopRRScheduler : public Scheduler {
    public:
        CoopRRScheduler(long period);
        void bind(Task *task);
        void schedule();

    private:
        TimerImpl *timer;
        Task *tasks[MAX_OCCUPATION];
        int occupation;
        long period;
};

#endif