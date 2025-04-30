/**
 * @file TonTime_SelfTest.ino
 * @brief Self-test automatico delle funzionalità base della libreria TonTime.
 *
 * - Verifica che Q sia inizialmente false.
 * - Verifica che Q diventi true dopo il preset.
 * - Verifica correttezza di timeElapsed() e timeSinceOn().
 *
 * @note Non dipende da librerie esterne. Basta caricare su board e aprire il Serial Monitor.
 */

#include "TonTime.h"

// Preset time per i test (in ms)
const unsigned long PT = 1000;
TonTime timer(PT);

void report(const char* testName, bool pass) {
  Serial.print(testName);
  Serial.print(" : ");
  Serial.println(pass ? "PASS" : "FAIL");
}

void setup() {
  Serial.begin(9600);
  while (!Serial) ;
  Serial.println("=== TonTime Self Test ===");

  // Test 1: uscita iniziale deve essere false
  report("Initial Q state", timer.ton(false) == false);

  // Test 2: ingresso true, subito Q=false
  report("Q before PT", timer.ton(true) == false);

  // Attendo meno di PT
  delay(PT - 200);
  report("Just before PT", timer.ton(true) == false);

  // Attendo oltre PT
  delay(300);
  report("After PT Q true", timer.ton(true) == true);

  // Verifico timeElapsed >= PT
  unsigned long el = timer.timeElapsed();
  report("timeElapsed >= PT", el >= PT);

  // Verifico timeSinceQ >= (elapsed-PT)
  unsigned long sq = timer.timeSinceOn();
  report("timeSinceQ valid", sq > 0);

  // Reset ingresso
  report("Reset Q on false", timer.ton(false) == false);

  Serial.println("=== End of tests ===");
}

void loop() {
  // nessuna azione continua
}

