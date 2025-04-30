/**
 * @file QuickStart.ino
 * @brief Esempio minimo di utilizzo della libreria TonTime.
 *
 * - Accende un LED se il pulsante viene premuto per almeno 2 secondi.
 * - Dimostra l'uso più semplice del metodo ton().
 */

#include <TonTime.h>

TonTime ledTimer(2000);
const int buttonPin = 2;
const int ledPin = 13;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  bool timer_Q = ledTimer.ton(digitalRead(buttonPin));
  digitalWrite(ledPin, timer_Q);
}