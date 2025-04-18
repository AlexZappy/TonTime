#include "TonTime.h"
#include <Arduino.h>

const int LED_PIN = 13;
const unsigned long DELAY_TIME = 4000; // 5 secondi

bool xAct = false;
TonTime t(DELAY_TIME);  // CORRETTO: usa DELAY_TIME

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
// Simula segnale: attivo 5s, spento 5s
xAct = (millis() / 1000) % 10 < 5;

t.update(xAct);

Serial.print("xAct: ");
Serial.print(xAct);
Serial.print(" | isRunning: ");
Serial.print(t.isRunning());
Serial.print(" | Elapsed: ");
Serial.print(t.timeElapsed());
Serial.print(" | Remaining: ");
Serial.println(t.timeRemaining());

delay(500);
digitalWrite(LED_PIN, xAct ? HIGH : LOW);
}
