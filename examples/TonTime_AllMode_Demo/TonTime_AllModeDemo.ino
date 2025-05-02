/**
 * @file TonTime_AllModesDemo.ino
 * @brief Esempio di utilizzo di tutte le modalità di TonTime.
 * Premere il pulsante per testare CLASSIC, TOGGLE, RETRIGGER.
 */

 #include "TonTime.h"

 const int buttonPin = 2;
 const int ledPin = 13;
 
 TonTime timer(3000);  // PT --> preset di 3 secondi
 
 void setup() {
   pinMode(buttonPin, INPUT_PULLUP);
   pinMode(ledPin, OUTPUT);
   Serial.begin(9600);
 
   Serial.println("=== TonTime Demo ===");
   
   // TEST: attiva qui la modalità che vuoi
   timer.setMode(TonTime::Classic);
   //timer.setMode(TonTime::Toggle);
   //timer.setMode(TonTime::Retrigger);
 }
 
 void loop() {
   bool input = digitalRead(buttonPin) == LOW;  // pulsante a massa
   bool q = timer.ton(input);
 
   digitalWrite(ledPin, q);
 
   Serial.print("xAct: ");
   Serial.print(input);
   Serial.print(" | Q: ");
   Serial.print(q);
   Serial.print(" | Elapsed: ");
   Serial.print(timer.timeElapsed());
   Serial.print(" | SinceOn: ");
   Serial.print(timer.timeSinceOn());
   Serial.print(" | Remaining: ");
   Serial.println(timer.timeRemaining());
 
   delay(200);
 }
 