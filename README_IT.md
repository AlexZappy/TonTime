# TonTime

**TonTime** è una libreria Arduino ispirata al comportamento del timer TON dei PLC. Permette di attivare un'uscita solo dopo che un ingresso è rimasto attivo per un tempo minimo definito, usando `millis()` e senza bloccare l'esecuzione.

## ⚙️ Caratteristiche principali

- Logica TON (Timer ON-Delay) compatibile con ambienti embedded
- Completamente non bloccante (`millis()`)
- Intervallo fisso impostato all'inizializzazione
- Accesso a tempo rimanente, trascorso e stato

## 📚 API della libreria

| Metodo             | Descrizione                                                       |
|--------------------|-------------------------------------------------------------------|
| `update()`         | Chiama ciclicamente: restituisce `true` quando il tempo è scaduto |
| `reset()`          | Annulla il conteggio in corso                                     |
| `isRunning()`      | Ritorna `true` se il timer è attivo                               |
| `getDelay()`       | Ritorna il tempo di ritardo impostato                             |
| `timeRemaining()`  | Millisecondi mancanti allo scadere                                |
| `timeElapsed()`    | Millisecondi trascorsi dall'inizio                                |

## 🧪 Esempio base

```cpp
#include <TonTime.h>
TonTime timer(false, 3000);

void loop() {
  timer.xStarted = digitalRead(2) == LOW;
  digitalWrite(13, timer.update());
}
```

## 📄 Licenza

MIT License – sviluppata da [AlexZappy](https://github.com/AlexZappy)
