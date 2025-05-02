
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

 TonTime::TonTime(unsigned long delayMillis):
       _delayTime(delayMillis),
       _startTimer(0),
       _active(false),
       _q(false),
       _tonTrue(0),
       _mode(Classic)
 {}
 
/**
 * @brief Imposta direttamente la modalità operativa del timer.
 *
 * Sostituisce il valore interno di `_mode` con il parametro fornito.
 * Permette di combinare più modalità utilizzando OR binario tra flag
 * (es. `TonMode::Classic | TonMode::Toggle`).
 *
 * @param modeFlags Maschera di modalità da impostare (bitwise flag).
 * Se non viene richiamato il metodo allora il TonTime sarà come default Classic
 */
void TonTime::setMode(uint8_t modeFlags) {  ///< TonMode :: Classic | ToggleMode :: Toggle; permette di inserirne più di uno per volta
    _mode = modeFlags;
}

/**
 * @brief Attiva o disattiva la modalità toggle del timer.
 *
 * Se attivata, la modalità toggle consente di spegnere Q con un nuovo fronte di xAct,
 * come in un relè passo-passo. Altrimenti, il comportamento resta quello classico TON.
 *
 * @param enabled `true` per abilitare il toggle, `false` per disattivarlo.
 */
void TonTime::enableToggleMode(bool enabled) {
    if (enabled) _mode |= Toggle;
    else _mode &= ~Toggle;
}


 /* ---------------------------------------------------------------------------*/
 /* ton() – logica PLC TON                                                     */
 /* ---------------------------------------------------------------------------*/
/**
 * @brief Esegue la logica del timer TON, con supporto modalità Toggle.
 *
 * - Classic: @c Q si attiva dopo PT ms se in resta true
 * - Toggle: @c Q cambia stato (toggle) ogni volta che in resta true per PT ms
 * 
 * @param in ingresso logico (xAct)
 * @return stato dell’uscita @c Q
 */
bool TonTime::ton(bool in)
{
    unsigned long now = millis();   ///< leggi tempo corrente
    bool timeElapsed;

    ///< Fronte di salita: inizia il conteggio se @param in è @c true e il timer non è attivo
    if (in && !_active) {
        _active     = true;
        _startTimer = now;
    }

    ///< Reset della modalità Classic: se in è falso e NON sono in modalità Toggle
    if (!in && !(_mode & Toggle) && !(_mode & Retrigger)) {
        _active = false;            ///< interrompe il conteggio
        _q = false;                 ///< resetta Q
    }

    timeElapsed = (now - _startTimer >= _delayTime);

    ///< Se in modalità Retrigger: mentre il timer è attivo e non è ancora scaduto, ogni nuovo in=1 fa ripartire
    if ((_mode & Retrigger) && _active && !timeElapsed && in)   ///< se sono in modalità retrigger e son già partito,
                                                                ///< non ho ancora raggiunto il tempo e ho in
    {
        _startTimer = now;          ///< Ripristino il conteggio
    }

    ///< Se il timer è attivo e il tempo è trascorso
    if (_active && timeElapsed) {

        if (_mode & Toggle) {
            _q = !_q;               ///< Modalità Toggle: cambia lo stato di Q (ON→OFF, OFF→ON)
            _active = false;        ///< disattiva temporaneamente il timer fino al prossimo fronte
        } else {
            _q = true;              ///< Modalità Classic: attiva Q una volta che il tempo è scaduto
        }
    }
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
  * evitando underflow quando @param millis() supera @param _delayTime.
  */

 unsigned long TonTime::timeRemaining() const
 {
     if (!_active) return _delayTime;
     unsigned long elapsed = millis() - _startTimer;
     return (elapsed >= _delayTime) ? 0 : _delayTime - elapsed;
 }
 

