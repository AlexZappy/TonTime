#ifndef TONTIME_H
#define TONTIME_H

#include <Arduino.h>

/**
 * @file TonTime.h
 * @brief Blocco Timer ON‑delay (TON) stile PLC per Arduino.
 *
 * Chiamare update() ciclicamente (tipicamente dentro loop()).
 * - Quando @c xStarted diventa @c true il timer parte.
 * - Se l'ingresso resta attivo per @c getDelay() millisecondi consecutivi,
 *   update() restituisce @c true.
 * - Se @c xStarted torna @c false prima dello scadere, il conteggio si azzera.
 *
 * Esempio:
 * @code{.cpp}
 * TonTime myTimer(false, 3000); // ritardo di 3 s
 *
 * void loop() {
 *   myTimer.xStarted = digitalRead(buttonPin) == HIGH;
 *   bool done = myTimer.update();
 *   digitalWrite(ledPin, done);
 * }
 * @endcode
 */
class TonTime
{
private:
    const unsigned long _delayMs;   ///< ritardo (preset time) in ms
    unsigned long _endTime;         ///< istante in cui il timer scadrà
    bool _started;                  ///< flag conteggio in corso

public:
    bool xStarted;                  ///< ingresso logico (impostare prima di update)

    /**
     * @brief Costruttore
     * @param startState  valore iniziale di @c xStarted
     * @param delayMs     ritardo ON‑delay in millisecondi
     */
    TonTime(bool startState, unsigned long delayMs);

    /**
     * @brief Avanza il timer.
     * @return @c true quando il ritardo è trascorso, altrimenti @c false.
     *
     * Va chiamata ad ogni ciclo; usa il campo pubblico @c xStarted come ingresso.
     */
    bool update();

    /**
     * @brief Resetta lo stato interno del timer.
     *
     * Non modifica il preset (@c getDelay()).
     */
    void reset();//  {_started = false; _endTime = 0;}

    /** @brief Millisecondi mancanti alla scadenza (0 se non conta o scaduto). */
    unsigned long timeRemaining() const;

    /** @brief Millisecondi trascorsi dall'avvio del conteggio (0 se fermo). */
    unsigned long timeElapsed() const;

    /** @brief @c true se il timer è in fase di conteggio, altrimenti @c false. */
    bool isRunning() const; // { return _started; }

    /** @brief Ritorna il preset time in millisecondi. */
    unsigned long getDelay() const; // { return _delayMs; }
};

#endif // TONTIME_H
