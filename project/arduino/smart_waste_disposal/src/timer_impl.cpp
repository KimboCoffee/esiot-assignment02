#include "timer_impl.h"

TimerImpl::TimerImpl(int period) {
    this->timer = new Timer();
    this->timer->start();
    this->period = period;
}

void TimerImpl::setPeriod(int period) {
    this->period = period;
}

void TimerImpl::waitForNextTick() {
    while(this->timer->read() < this->period);
    this->timer->pause();
    this->timer->start();
}