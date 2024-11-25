#include <Arduino.h>
#include "dummy_task.h"

DummyTask::DummyTask(long period) {
    this->period = period;
    this->stepCount = 0;
    this->prevVal = 0;
}

void DummyTask::step(long schedPeriod) {
    if (schedPeriod * this->stepCount >= this->period) {
        this->stepCount = 0;
        this->prevVal++;
    } else this->stepCount++;
    Serial.println(this->prevVal);
    Serial.println(this->stepCount);
}