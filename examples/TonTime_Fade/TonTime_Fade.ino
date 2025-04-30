/**
 * @file TonTime_Fade.ino
 * @brief Sfumatura della luminosità di un LED basata su TonTime.timeElapsed().
 *
 * - Il LED passa da spento a massimo in 2 secondi dopo la pressione del pulsante.
 * - Utilizza analogWrite() per PWM.
 */

#include "TonTime.h"

const int buttonPin = 2;      // ingresso pulsante
const int ledPin    = 9;      // pin PWM per LED
const unsigned long preset = 2000;  // 2 secondi
TonTime ledTimer(preset);

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // pulsante a massa
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Legge l'ingresso: LOW = premuto
  bool in = (digitalRead(buttonPin) == LOW);

  // Aggiorna TON, ma non serve Q in questo sketch
  ledTimer.ton(in);

  // Tempo trascorso dall'avvio (0 se release)
  unsigned long et = ledTimer.timeElapsed();

  // Mappa [0 … preset] in [0 … 255]
  int pwm;
  if (et < preset) {
    pwm = map(et, 0, preset, 0, 255);
  } else {
    pwm = 255;  // piena luminosità dopo il preset
  }

  analogWrite(ledPin, pwm);

  // Breve delay per stabilità
  delay(20);
}

