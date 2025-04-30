
# TonTime

---

**TonTime**
 is an Arduino library that replicates the TON (on-delay) timer logic found in industrial PLCs. It enables you to trigger an output only after an input has remained active for a fixed duration, using non-blocking `millis()` logic

---

## ⚙️ Features

- PLC-style TON (on-delay) timer logic
- Fully non-blocking (uses `millis()`)
- Delay time set at construction
- Output Q becomes `true` only after the preset time has elapsed
- Output remains `true` while the input stays high
- Resets immediately when the input drops (unless latch mode is implemented)
- Provides utility functions to track elapsed and remaining time

---

## 📚 API Reference

| Method               | Description                                                                 |
|----------------------|-----------------------------------------------------------------------------|
| `TonTime(delayMs)`   | Constructor. Sets the preset delay in milliseconds                          |
| `bool ton(bool xAct)`| Call repeatedly. Returns `true` (Q) when time has elapsed                   |
| `timeElapsed()`      | Returns time in ms since input became active (xAct = true)                  |
| `timeRemaining()`    | Returns time remaining before output Q becomes `true`                       |
| `timeSinceOn()`      | Returns ms since Q became `true`, or 0 if Q is false                        |

---

## 🧪 Basic Example

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

## 📂 Included Examples

| Example folder            | Description                                                                 |
|---------------------------|-----------------------------------------------------------------------------|
| `TonTime_QuickStart`      | Minimal working example with button and LED                                 |
| `TonTime_Basics_Led`      | Uses `timeElapsed()` and `timeSinceOn()` to show internal state via Serial  |
| `TonTime_Fade`            | Maps `timeElapsed()` to LED PWM brightness                                 |
| `TonTime_SelfTest`        | Automated self-test of timer behavior via Serial                            |

---

## 🛠️ Installation

### Arduino IDE

1. Clone or download this repo as `.zip`
2. Place it inside your `Arduino/libraries` folder
3. Restart the IDE

### PlatformIO

Add to your `platformio.ini`:

```ini
lib_deps = 
  https://github.com/YourUsername/TonTime.git
```

---

## 📄 License

MIT License  
Created and maintained by [AlexZappy](https://github.com/AlexZappy)

---
