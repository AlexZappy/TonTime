#include <TonTime.h>

TonTime ledTimer(false, 2000);
const int buttonPin = 2;
const int ledPin = 13;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  ledTimer.xStarted = digitalRead(buttonPin) == LOW;
  digitalWrite(ledPin, ledTimer.update());
}