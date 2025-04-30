
# TonTime

---
**TonTime** è una libreria per Arduino che replica il comportamento del timer TON (ritardo all’attivazione) utilizzato nei PLC industriali.  
Permette di attivare un’uscita (Q) solo dopo che un ingresso è rimasto attivo per una durata prefissata, utilizzando logica non bloccante basata su `millis()`.

---

## ⚙️ Funzionalità

- Timer in stile PLC (TON – ritardo all’attivazione)
- Completamente non bloccante (usa `millis()`)
- Tempo di ritardo impostato nel costruttore
- L’uscita Q diventa `true` solo dopo il tempo prefissato
- Q resta `true` finché l’ingresso rimane attivo
- Reset immediato se l’ingresso torna `false`
- Funzioni accessorie per tempo trascorso e rimanente

---

## 📚 Riferimento API

| Metodo                | Descrizione                                                              |
|-----------------------|--------------------------------------------------------------------------|
| `TonTime(delayMs)`    | Costruttore: imposta il tempo di ritardo in millisecondi                |
| `bool ton(bool xAct)` | Chiamare ripetutamente; restituisce `true` (Q) quando il ritardo è scaduto |
| `timeElapsed()`       | Ritorna il tempo trascorso (in ms) da quando l’ingresso è diventato `true` |
| `timeRemaining()`     | Ritorna il tempo rimanente (in ms) allo scadere                          |
| `timeSinceOn()`       | Ritorna il tempo da quando Q è diventato `true` (0 se Q è `false`)       |

---

## 🧪 Esempio base

```cpp
#include <TonTime.h>

const int btn = 2;
const int led = 13;

TonTime ton(3000); // 3 secondi

void setup() {
  pinMode(btn, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
  bool q = ton.ton(digitalRead(btn) == LOW);
  digitalWrite(led, q);
}
```

---

## 📂 Esempi inclusi

| Cartella esempio         | Descrizione                                                              |
|--------------------------|---------------------------------------------------------------------------|
| `TonTime_QuickStart`     | Esempio minimo con pulsante e LED                                         |
| `TonTime_Basics_Led`     | Mostra anche `timeElapsed()` e `timeSinceOn()` con output su Serial       |
| `TonTime_Fade`           | Usa `timeElapsed()` per sfumare un LED in PWM                             |
| `TonTime_SelfTest`       | Esegue una serie di test automatici per validare il comportamento del timer |

---

## 🛠️ Installazione

### Arduino IDE

1. Scarica o clona la repo come `.zip`
2. Estrai nella cartella `Arduino/libraries`
3. Riavvia l’IDE

### PlatformIO

Aggiungi nel tuo `platformio.ini`:

```ini
lib_deps = 
  https://github.com/YourUsername/TonTime.git
```

---

## 📄 Licenza

Distribuita sotto licenza **MIT**  
Autore: [AlexZappy](https://github.com/AlexZappy)

---
