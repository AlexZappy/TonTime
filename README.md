# TonTime – Arduino Library

## 📝 About (English)

**TonTime** is an Arduino library inspired by the PLC-style TON (on-delay) timer logic.  
It implements a non-blocking timer using `millis()`, suitable for state machines, button debouncing, and industrial-like logic.

### ⚙️ Features

- TON (on-delay) behavior
- Non-blocking (uses `millis()`)
- Supports multiple modes: Classic, Toggle, Retrigger
- Utility methods: `timeElapsed()`, `timeRemaining()`, `timeSinceOn()`
- Configurable using `setMode()` or `enableXXXMode()`

---

## 🇮🇹 Informazioni (Italiano)

**TonTime** è una libreria Arduino ispirata alla logica PLC del timer TON (ritardo all'attivazione).  
Implementa un timer non bloccante usando `millis()`, utile per macchine a stati, gestione pulsanti, logiche industriali.

### ⚙️ Caratteristiche

- Comportamento TON (ritardo ON)
- Non bloccante (`millis()`)
- Supporta modalità multiple: Classic, Toggle, Retrigger
- Metodi utilità: `timeElapsed()`, `timeRemaining()`, `timeSinceOn()`
- Configurabile con `setMode()` o `enableXXXMode()`

---

## 📚 API

| Method               | Description (EN)                  | Descrizione (IT)                 |
|---------------------|---------------------------------|----------------------------------|
| `ton(bool)`          | Executes timer logic             | Esegue la logica del timer       |
| `setMode(flags)`     | Set operational modes            | Imposta le modalità operative    |
| `enableToggleMode()` | Enable/disable toggle mode       | Abilita/disabilita modalità toggle |
| `timeElapsed()`      | Elapsed time since start         | Tempo trascorso dall'avvio       |
| `timeRemaining()`    | Remaining time to timeout        | Tempo rimanente alla scadenza    |
| `timeSinceOn()`      | Time since Q became true         | Tempo da quando Q è true         |

---

## 💻 Example

```cpp
#include <TonTime.h>

TonTime timer(3000);
timer.setMode(TonTime::Classic); // or Toggle, Retrigger

void loop() {
  bool input = digitalRead(2) == LOW;
  bool q = timer.ton(input);
  digitalWrite(13, q);
}
```

---

## 📁 Example files

examples/TonTime_AllModesDemo/: Shows Classic, Toggle, Retrigger behavior

---

## Changelog

See [CHANGELOG.md](CHANGELOG.md) for version history.

---

## License

- MIT [License](LICENSE) – Created by Alex Zappy

- [![GitHub repo](https://img.shields.io/badge/GitHub-TonTime-blue?logo=github)](https://github.com/AlexZappy/TonTime)
