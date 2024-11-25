#include "coop_r_r_scheduler.h"

#define NO_PERIOD -1

CoopRRScheduler::CoopRRScheduler(long period) {
    this->period = period;
    this->occupation = 0;
    this->timer = new TimerImpl(this->period);
}

void CoopRRScheduler::bind(Task *task) {
    if (this->occupation < MAX_OCCUPATION) {
        this->tasks[occupation] = task;
        this->occupation++;
    }
}

void CoopRRScheduler::schedule() {
    timer->waitForNextTick();
    Serial.println(this->period);
    for (int i=0; i<this->occupation; i++) {
        tasks[i]->step(this->period);
    }
}