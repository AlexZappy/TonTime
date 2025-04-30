/**
 * @file TonTime.h
 * @brief Timer ON‑delay (TON) stile Siemens per Arduino.
 *
 * Chiamare <code>ton(in)</code> ciclicamente (di solito in <code>loop()</code>):
 *  - Se l'ingresso <b>in</b> resta TRUE per <b>PT</b> ms consecutivi, l'uscita <b>Q</b> diventa TRUE.
 *  - Q rimane TRUE finché l'ingresso resta TRUE.
 *  - Quando in torna FALSE, Q si azzera immediatamente e il conteggio riparte al prossimo fronte di salita.
 */

 #ifndef TONTIME_H
 #define TONTIME_H
 
 #include <Arduino.h>
 
 class TonTime {
 private:
     const unsigned long _delayTime;   ///< PT: ritardo impostato in millisecondi
     unsigned long _startTimer;        ///< Timestamp del fronte di salita di IN
     bool _active;                     ///< TRUE se il timer è in conteggio
     bool _q = false;                  ///< Uscita Q (privata)
     mutable unsigned long _tonTrue = 0; ///< Timestamp di quando Q è diventata TRUE (mutable per accessor const)
 
 public:
     /**
      * @brief Costruttore
      * @param delayMillis  preset time (PT) in millisecondi.
      */
     explicit TonTime(unsigned long delayMillis);
 
     /**
      * @brief Esegue la logica TON.
      * @param in  ingresso BOOL (TRUE per tenere il timer attivo).
      * @return TRUE (Q) quando il ritardo è trascorso e finché @p in resta TRUE.
      */
     bool ton(bool in);
 
     /**
      * @brief Millisecondi trascorsi dal fronte di salita di IN.
      * @return Et (Elapsed Time); 0 se il timer non è in conteggio.
      */
     unsigned long timeElapsed() const;
 
     /**
      * @brief Millisecondi mancanti al raggiungimento di PT.
      * @return PT‑ET; 0 se il timer è scaduto o fermo.
      */
     unsigned long timeRemaining() const;
 
     /**
      * @brief Tempo trascorso da quando Q è diventata TRUE.
      * @return millisecondi; 0 se Q è FALSE.
      */
     unsigned long timeSinceOn();
 };
 
 #endif // TONTIME_H