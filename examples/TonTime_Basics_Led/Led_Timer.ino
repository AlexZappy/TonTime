/**
 * @file LedTimer.ino
 * @brief Esempio base di utilizzo della libreria TonTime.
 *
 * Il LED si accende solo se il pulsante rimane premuto per almeno 2 secondi.
 * Stampa su seriale il tempo trascorso e il tempo da quando Q è diventato true.
 */


#include "TonTime.h"

const int btn = 2;
const int led = 13;

TonTime ton(2000);      // millisecondi

void setup() {
  pinMode(btn, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  bool in = digitalRead(btn) == LOW;       // pulsante a massa
  bool q  = ton.ton(in);
  digitalWrite(led, q);

  Serial.print("Elapsed: ");
  Serial.print(ton.timeElapsed());       // tempo trascorso
  Serial.print("  SinceQ: ");
  Serial.println(ton.timeSinceOn());        // tempo trascorso da quando è stato acceso

  delay(200);
}