
# TonTime - Branch di Sviluppo: `feature-tonToggle`

---
Questo ramo contiene lo sviluppo di una nuova funzionalità sperimentale della libreria **TonTime**.

---

## 🌟 Obiettivo

Implementare un’opzione per il comportamento del metodo `ton()` che consenta di:

- Attivare `Q` dopo il tempo `PT` come da logica TON classica
- Spegnere `Q` **con un nuovo fronte di `xAct`** (toggle), invece che al ritorno a `false`

Questo consente di simulare un comportamento **tipo relè passo-passo**, utile in logiche di controllo alternative.

---

## 🔄 Stato attuale dello sviluppo

- [x] Creazione del branch `feature-tonToggle`
- [x] Definizione della variabile di modalità (es. `mode = TOGGLE`)
- [ ] Aggiornamento metodo `ton()` per supportare la nuova modalità
- [ ] Aggiunta di flag di stato interno per riconoscere i fronti
- [ ] Test locali su esempio `TonTime_ToggleTest.ino`
- [ ] Verifica compatibilità retroattiva con i vecchi sketch
- [ ] Documentazione aggiornata (`README.md`, `Doxygen`)

---

## ⚙️ Strategia di implementazione

- Aggiunta opzione (es. `bool toggleMode = false`) nel costruttore o tramite metodo `enableToggleMode(true)`
- All’interno di `ton(xAct)`, rilevare un fronte di salita per spegnere `Q` se già attivo
- Mantenere compatibilità con il comportamento classico TON per default

---

## 📂 File coinvolti

- `TonTime.h` → nuova variabile di configurazione, nuovo stato
- `TonTime.cpp` → logica del metodo `ton()` modificata
- `examples/TonToggleDemo/TonToggleDemo.ino` → sketch di esempio
- `README_dev.md` → questo file
- (facoltativo) `CHANGELOG.md`

---

## 📌 Note per l’integrazione finale

- Prima della fusione nel branch `main`, testare ampiamente con i progetti esistenti
- Mantenere comportamento predefinito identico alla versione 2.0.0b
- Considerare rilascio come `v2.1.0`

---

## 🧪 Suggerimenti per i test

- Pulsante su `pin 2`, LED su `pin 13`
- Premere → attende PT → accende LED
- Premere nuovamente → spegne LED se `toggleMode = true`

---
