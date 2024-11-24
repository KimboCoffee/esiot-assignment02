#include <Arduino.h>
#include "dummy_task.h"

DummyTask::DummyTask(long period) {
    this->period = period;
    this->stepCount = 0;
}

void DummyTask::step(long schedPeriod) {
    if (schedPeriod * this->stepCount >= this->period) {
        this->stepCount = 0;
        Serial.println("Action performed !");
    } else this->stepCount++;
}