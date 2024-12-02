#include <Arduino.h>
#include <avr/sleep.h>
#include "container_handler_task.h"
#include "servo_door.h"
#include "button_impl.h"
#include "lcd_screen.h"
#include "led.h"
#include "pir_user_detector.h"

/*timeouts*/
#define NO_USER_TIME_LIMIT 10000
#define MAX_OPENING_TIME 10000
#define CLOSING_TIME 2000
#define EMPTYING_TIME 5000

/*digital pins*/
#define GREEN_LED 12
#define RED_LED 13
#define OPEN_BUTTON 11
#define CLOSE_BUTTON 10
#define DOOR 9
#define USER_DETECTOR 2

/*LCD specs*/
#define LCD_ADDRESS 0x27
#define LCD_ROWS 4
#define LCD_COLS 20

void wakeUp() {}

ContainerHandlerTask::ContainerHandlerTask(int period, SystemStateTracker *systemTracker) {
    this->period = period;
    this->systemTracker = systemTracker;
    this->schedSteps = 0;
    this->noUserSteps = 0;
    this->openSteps = 0;
    this->door = new ServoDoor(DOOR);
    this->openButton = new ButtonImpl(OPEN_BUTTON);
    this->closeButton = new ButtonImpl(CLOSE_BUTTON);
    this->userScreen = new LCDScreen(LCD_ADDRESS, LCD_ROWS, LCD_COLS);
    this->greenLight = new Led(GREEN_LED);
    this->redLight = new Led(RED_LED);
    this->userDetector = new PIRUserDetector(USER_DETECTOR);
    this->setState(CONTAINER_ACCEPTING_WASTE);
}

void ContainerHandlerTask::step(int schedPeriod) {
    if (this->schedSteps * schedPeriod >= this->period) {
        switch (this->state) {
            case CONTAINER_ACCEPTING_WASTE:
                this->noUserSteps++;
                if (this->systemTracker->isTempExceeded()) {
                    this->setState(CONTAINER_TEMP_EXCEEDED);
                } else if (this->systemTracker->isLevelExceeded()) {
                    this->setState(CONTAINER_LEVEL_EXCEEDED);
                } else if (this->openButton->isPressed()) {
                    this->setState(CONTAINER_OPEN);
                } else if (this->noUserSteps * this->period >= NO_USER_TIME_LIMIT) {
                    this->setState(CONTAINER_DEEP_SLEEP_WORKING);
                }
                break;

            case CONTAINER_OPEN:
                this->openSteps++;
                if (this->systemTracker->isTempExceeded()) {
                    this->setState(CONTAINER_TEMP_EXCEEDED);
                } else if (this->systemTracker->isLevelExceeded()) {
                    this->setState(CONTAINER_LEVEL_EXCEEDED);
                } else if (this->closeButton-> isPressed() || this->openSteps * this->period >= MAX_OPENING_TIME) {
                    this->setState(CONTAINER_CLOSING);
                }
                break;

            case CONTAINER_CLOSING:
                this->closingSteps++;
                if (this->systemTracker->isTempExceeded()) {
                    this->setState(CONTAINER_TEMP_EXCEEDED);
                } else if (this->closingSteps * this->period >= CLOSING_TIME) {
                        this->setState(CONTAINER_ACCEPTING_WASTE);
                }
                break;

            case CONTAINER_DEEP_SLEEP_WORKING:
                detachInterrupt(digitalPinToInterrupt(USER_DETECTOR));
                this->setState(CONTAINER_ACCEPTING_WASTE);
                break;

            case CONTAINER_TEMP_EXCEEDED:
                this->noUserSteps++;
                if (this->noUserSteps * this->period >= NO_USER_TIME_LIMIT) {
                    this->setState(CONTAINER_DEEP_SLEEP_NONWORKING);
                } else if (!this->systemTracker->isTempExceeded()) {
                    this->setState(CONTAINER_ACCEPTING_WASTE);
                }
                break;

            case CONTAINER_LEVEL_EXCEEDED:
                this->noUserSteps++;
                if (this->noUserSteps * this->period >= NO_USER_TIME_LIMIT) {
                    this->setState(CONTAINER_DEEP_SLEEP_NONWORKING);
                } else if (!this->systemTracker->isLevelExceeded()) {
                    this->setState(CONTAINER_ACCEPTING_WASTE);
                }
                break;

            case CONTAINER_EMPTYING:
                this->emptyingSteps++;
                if (this->emptyingSteps * this->period >= EMPTYING_TIME) {
                    if (this->systemTracker->isTempExceeded()) {
                        this->setState(CONTAINER_TEMP_EXCEEDED);
                    } else {
                        this->setState(CONTAINER_ACCEPTING_WASTE);
                    }
                }
                break;

            case CONTAINER_DEEP_SLEEP_NONWORKING:
                detachInterrupt(digitalPinToInterrupt(USER_DETECTOR));
                if (this->systemTracker->isLevelExceeded()) {
                    this->setState(CONTAINER_LEVEL_EXCEEDED);
                } else {
                    this->setState(CONTAINER_TEMP_EXCEEDED);
                }
                break;
        }
    }
    this->schedSteps++;
}

void ContainerHandlerTask::setState(ContainerHandlerState state) {
    this->state = state;
    switch(state) {
        case CONTAINER_ACCEPTING_WASTE:
            this->noUserSteps = 0;
            this->redLight->turnOff();
            this->greenLight->turnOn();
            this->door->unlock();
            this->door->close();
            this->door->lock();
            this->userScreen->println(1, "Press Open");
            this->userScreen->println(2, "to enter waste");
            break;

        case CONTAINER_OPEN:
            this->openSteps = 0;
            this->door->unlock();
            this->door->openForInsertion();
            this->door->lock();
            this->userScreen->println(1, "Press close");
            this->userScreen->println(2, "when done");
            break;

        case CONTAINER_CLOSING:
            this->closingSteps = 0;
            this->door->unlock();
            this->door->close();
            this->door->lock();
            this->userScreen->println(1, "Waste received");
            break;

        case CONTAINER_DEEP_SLEEP_WORKING:
            this->userScreen->turnOff();
            this->goToSleep();
            break;

        case CONTAINER_TEMP_EXCEEDED:
            this->noUserSteps = 0;
            this->door->unlock();
            this->door->close();
            this->door->lock();
            this->greenLight->turnOff();
            this->redLight->turnOn();
            this->userScreen->println(1, "Problem detected:");
            this->userScreen->println(2, "door is locked");
            break;

        case CONTAINER_LEVEL_EXCEEDED:
            this->noUserSteps = 0;
            this->door->unlock();
            this->door->close();
            this->door->lock();
            this->greenLight->turnOff();
            this->redLight->turnOn();
            this->userScreen->println(1, "Container full:");
            this->userScreen->println(2, "door is locked");
            break;

        case CONTAINER_EMPTYING:
            this->emptyingSteps = 0;
            this->door->unlock();
            this->door->openForEmptying();
            this->door->lock();
            break;

        case CONTAINER_DEEP_SLEEP_NONWORKING:
            this->userScreen->turnOff();
            this->goToSleep();
            break;
    }
}

void ContainerHandlerTask::goToSleep() {
    attachInterrupt(digitalPinToInterrupt(USER_DETECTOR), wakeUp, RISING);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
}
