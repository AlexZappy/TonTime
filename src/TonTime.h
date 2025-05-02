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
 /**
  * @brief Definizione della classe
  * @par _delayTime ritardo impostato in millisecondi
  * @par _startTimer Timestamp del fronte di salita di IN
  * @par _active TRUE se il timer è in conteggio
  * @par _q Uscita Q (privata)
  * @par _tonTrue Timestamp di quando Q è diventata TRUE (mutable per accessor const)
  * @par _mode Variabile per la configurazione, di defaul Classic
  */
 class TonTime {
 private:
     const unsigned long _delayTime;    ///< PT: ritardo impostato in millisecondi
     unsigned long _startTimer;         ///< Timestamp del fronte di salita di IN
     bool _active;                      ///< TRUE se il timer è in conteggio
     bool _memActive;
     bool _q;                           ///< Uscita Q (privata)
     mutable unsigned long _tonTrue;    ///< Timestamp di quando Q è diventata TRUE (mutable per accessor const)
     uint8_t _mode;                     ///< Variabile per la configurazione, di defaul Classic

 
 public:
    /**
     * @brief Modalità operative per il timer TON.
     * 
     * Ogni valore rappresenta una modalità attivabile tramite bitmask:
     * - Classic: comportamento standard TON
     * - Toggle: abilita lo spegnimento di Q con nuovo fronte xAct
     */
    enum TonMode {
        Classic     = 0x01, ///< TonTime Classic
        Toggle      = 0x02,
        Retrigger   = 0x03,   ///< TonTime Toggle with xAct
        // altri in futuro: Hold, Retriggerable, ecc.
    };
  
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
    
    /**
     * @brief Nuovi metodi per il set della modalità 
     */

     void setMode(uint8_t modeFlags);           ///< es: setMode(Classic | Toggle | Retrigger)

     void enableToggleMode(bool enabled);       ///< shortcut semplice
     void enableRetriggerMode(bool enabled);    ///< Abilita il modo retrigger
     

 };
 
 #endif // TONTIME_H