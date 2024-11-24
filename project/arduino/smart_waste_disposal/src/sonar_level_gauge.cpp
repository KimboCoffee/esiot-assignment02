#include <Arduino.h>
#include "sonar_level_gauge.h"

#define SPEED_OF_SOUND (331.45 + (0.62*25))
#define LOW_DIST_THRESHOLD 0.05
#define FULL 100.0
#define EMPTY 0.0

SonarLevelGauge::SonarLevelGauge(int trigPin, int echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    pinMode(this->trigPin, OUTPUT);
    pinMode(this->echoPin, INPUT);
    this->baseDist = this->getDistance();
}

float SonarLevelGauge::getFillingPercentage() {
    float d = this->getDistance();
    if (d < LOW_DIST_THRESHOLD) {
        return FULL;
    } else if (d > this->baseDist) {
        return EMPTY;
    } else {
        return (this->baseDist - d) / (this->baseDist - LOW_DIST_THRESHOLD) * 100;
    }
}

float SonarLevelGauge::getDistance() {
    digitalWrite(this->trigPin, LOW);
    delayMicroseconds(3);
    digitalWrite(this->trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(this->trigPin, LOW);

    float t = pulseIn(this->echoPin, HIGH) / 1000.0 / 1000.0 / 2.0;
    return t * SPEED_OF_SOUND;
}