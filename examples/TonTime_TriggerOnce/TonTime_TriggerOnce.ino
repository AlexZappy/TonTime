#include <TonTime.h>

TonTime triggerTimer(false, 3000);
bool triggered = false;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop() {
  if (!triggered) {
    triggerTimer.xStarted = digitalRead(2) == LOW;
    if (triggerTimer.update()) {
      digitalWrite(13, HIGH);
      triggered = true;
    }
  }
}