// /**
//  * @file TonTime.cpp
//  * @brief Implementazione della classe TonTime (Timer ON‑delay).
//  *
//  * Questa unità contiene la logica di runtime del timer:
//  *  - costruttore con lista di inizializzazione;
//  *  - metodo di aggiornamento ciclico;
//  *  - funzioni di utilità per tempo residuo, trascorso e stato.
//  */

//  #include "TonTime.h"

//  /* ---------------------------------------------------------------------------*/
//  /*  Costruttore                                                               */
//  /* ---------------------------------------------------------------------------*/
//  /**
//   * @param startState  stato iniziale del segnale d'ingresso (true = timer avviato)
//   * @param delayMs     tempo di ritardo in millisecondi
//   *
//   * Inizializza i membri:
//   *  - _delayMs   → preset immutabile del ritardo
//   *  - _endTime   → 0 indica timer non ancora attivo
//   *  - _started   → false, conteggio fermo
//   *  - xStarted   → copia di startState (ingresso logico)
//   */
//  TonTime::TonTime(bool startState, unsigned long delayMs)
//      : _delayMs(delayMs),
//        _endTime(0),
//        _started(false),
//        xStarted(startState)
//  {
//      // Nessuna logica aggiuntiva necessaria
//  }
 
//  /* ---------------------------------------------------------------------------*/
//  /*  update()                                                                  */
//  /* ---------------------------------------------------------------------------*/
//  /**
//   * @brief  Deve essere chiamato ciclicamente (tipicamente in loop()).
//   *
//   * Logica:
//   * 1. Se l'ingresso @c xStarted è alto e il timer non sta già contando,
//   *    memorizza l'istante di fine conteggio ed entra in stato @c _started.
//   * 2. Se il timer è in esecuzione e il tempo corrente supera @c _endTime,
//   *    termina il conteggio, disarma @c _started e restituisce @c true.
//   * 3. Se l'ingresso è basso, il timer si resetta.
//   *
//   * @return @c true  quando il tempo di ritardo è trascorso;
//   *         @c false in tutti gli altri casi.
//   */
//  bool TonTime::update()
//  {
//      unsigned long now = millis();
 
//      if (xStarted)                          // ingresso alto
//      {
//          if (!_started)                     // fronte di salita
//          {
//              _started = true;
//              _endTime = now + _delayMs;     // calcola scadenza
//          }
//          else if (now >= _endTime)          // tempo scaduto
//          {
//              _started = false;             // disarma per riuso
//              return true;                  // uscita ton
//          }
//      }
//      else                                   // ingresso basso
//      {
//          _started = false;                 // reset
//      }
//      return false;
//  }
 
//  /* ---------------------------------------------------------------------------*/
//  /*  timeRemaining()                                                           */
//  /* ---------------------------------------------------------------------------*/
//  /**
//   * @brief  Millisecondi mancanti allo scadere del timer.
//   *
//   * Se il timer non sta contando o è già terminato restituisce 0,
//   * evitando underflow quando @c millis() supera @c _endTime.
//   */
//  unsigned long TonTime::timeRemaining() const
//  {
//      unsigned long now = millis();
//      if (!_started || now >= _endTime)
//          return 0;
 
//      return _endTime - now;
//  }
 
//  /* ---------------------------------------------------------------------------*/
//  /*  timeElapsed()                                                             */
//  /* ---------------------------------------------------------------------------*/
//  /**
//   * @brief  Millisecondi trascorsi dall'avvio del conteggio.
//   *
//   * Restituisce 0 se il timer non è in esecuzione.
//   */
//  unsigned long TonTime::timeElapsed() const
//  {
//      if (!_started)
//          return 0;
 
//      unsigned long now = millis();
//      return now - (_endTime - _delayMs);
//  }
 
//  /* ---------------------------------------------------------------------------*/
//  /*  Accessor costanti                                                         */
//  /* ---------------------------------------------------------------------------*/
//  unsigned long TonTime::getDelay() const
//  {
//      return _delayMs;
//  }
 
//  bool TonTime::isRunning() const
//  {
//      return _started;
//  }
 

#include "TonTime.h"

TonTime::TonTime(unsigned long delayMillis) {
    delayTime = delayMillis;
    startTime = 0;
    active = false;
}

void TonTime::update(bool input) {
    if (input) {
        if (!active) {
            active = true;
            startTime = millis();
        }
    } else {
        active = false;
        startTime = 0;
    }
}

bool TonTime::isRunning() {
    if (!active) return false;

    unsigned long elapsed = millis() - startTime;
    return elapsed >= delayTime;
}


unsigned long TonTime::timeElapsed() {
    return active ? millis() - startTime : 0;
}

unsigned long TonTime::timeRemaining() {
    if (!active) return delayTime;
    unsigned long elapsed = millis() - startTime;
    return (elapsed >= delayTime) ? 0 : delayTime - elapsed;
}