#include <Arduino.h>

#define LED_OFFSET 11
#define CHAR_OFFSET 48

int i;
int period;

void setup() {
  Serial.begin(9600);
  i = 0;
  period = 500;
  for (int i=1; i<=2; i++) pinMode(i + LED_OFFSET, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, LOW);
  for (int k=1; k<=2; k++) digitalWrite(k + LED_OFFSET, LOW);

  Serial.println(period);
  Serial.println(i);
  Serial.println(0);
  Serial.println(i+1);
  Serial.println(0);
  i = (i + 1) % 100;

  if (Serial.available()) {
    digitalWrite(2, HIGH);
    int val = Serial.read();
    digitalWrite(val + LED_OFFSET - CHAR_OFFSET, HIGH);
  }
  delay(period);
}