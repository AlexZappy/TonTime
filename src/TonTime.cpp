
/**
 * @file TonTime.cpp
 * @brief Implementazione della classe @class TonTime (Timer ON‑delay).
 *
 * Questa unità contiene la logica di runtime del timer:
 *  
 *  - costruttore con lista di inizializzazione;
 *  - metodo di aggiornamento ciclico;
 *  - funzioni di utilità per tempo residuo, trascorso e stato.
 */

 #include "TonTime.h"

 /* ---------------------------------------------------------------------------*/
 /* Costruttore                                                                */
 /* ---------------------------------------------------------------------------*/
  /**
  * 
  * @param delayMillis     tempo di ritardo in millisecondi
  *
  * Inizializza i membri:
  *  - @param _delayTime   → preset del ritardo
  *  - @param _active   → false, conteggio fermo
  *  - @param _startTimer   → Timer Avviato
  */

 TonTime::TonTime(unsigned long delayMillis)
     : _delayTime(delayMillis),
       _startTimer(0),
       _active(false),
       _q(false),
       _tonTrue(0)
 {}
 
 /* ---------------------------------------------------------------------------*/
 /* ton() – logica PLC TON                                                     */
 /* ---------------------------------------------------------------------------*/
 /**   
    * @brief @c ton() Esegue il timer TON.
    * @param xAct Ingresso (TRUE per contare)
    * @return  _q – @c true quando il ritardo è trascorso e finché xAct resta TRUE.
    * @warning Quando viene letto il fornte di salita, il timer inizia il conteggio
    *           Quando il @param xAct torna false il conteggio smette e si azzera e @param Q torna @c false
    *
 */
 bool TonTime::ton(bool in)
 {
     // fronte di salita
     if (in && !_active) {
         _active     = true;
         _startTimer = millis();
     }
     // reset
     if (!in) {
         _active = false;
     }
 
     _q = _active && (millis() - _startTimer >= _delayTime);
     return _q;
 }
 
 /* ---------------------------------------------------------------------------*/
 /* timeSinceQ()                                                               */
 /* ---------------------------------------------------------------------------*/
  /**
  * @brief @c timeSinceQ() - restituisce il tempo trascorso da quando il contatore ha raggiunto 
  *         il tempo impostato
  * @return ETAct - come unsigned long
  */

 unsigned long TonTime::timeSinceOn()
 {
     if (_q && _tonTrue == 0) {
         _tonTrue = millis();
     } else if (!_q) {
         _tonTrue = 0;
     }
     return _tonTrue ? millis() - _tonTrue : 0;
 }
 
 /* ---------------------------------------------------------------------------*/
 /* timeElapsed()                                                              */
 /* ---------------------------------------------------------------------------*/
  /**
  * @brief  Millisecondi trascorsi dall'avvio del conteggio.
  *
  * @return ETAct - Restituisce @c 0 se il timer non è in esecuzione.
  */
 unsigned long TonTime::timeElapsed() const
 {
     return _active ? millis() - _startTimer : 0;
 }
 
 /* ---------------------------------------------------------------------------*/
 /* timeRemaining()                                                            */
 /* ---------------------------------------------------------------------------*/
  /**
  * @brief  Millisecondi mancanti allo scadere del timer.
  *
  * Se il timer non sta contando o è già terminato restituisce 0,
  * evitando underflow quando @param millis() supera @param _endTime.
  */

 unsigned long TonTime::timeRemaining() const
 {
     if (!_active) return _delayTime;
     unsigned long elapsed = millis() - _startTimer;
     return (elapsed >= _delayTime) ? 0 : _delayTime - elapsed;
 }
 