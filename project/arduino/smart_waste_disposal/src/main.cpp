#include <Arduino.h>

int i;
int period;

void setup() {
  Serial.begin(9600);
  i = 0;
  period = 1000;
}

void loop() {
  Serial.println(period);
  Serial.println(i);
  Serial.println(0);
  Serial.println(i+1);
  Serial.println(0);
  i = (i + 1) % 100;
  delay(period);
}