# TonTime

**TonTime** is an Arduino library inspired by the TON (on-delay) timer logic used in PLCs. It allows triggering an output only after an input has remained active for a fixed time, using non-blocking `millis()` logic.

## ⚙️ Features

- TON-style (on-delay) timer logic
- Fully non-blocking (uses `millis()`)
- Fixed delay at construction time
- Provides elapsed/remaining time and status checks

## 📚 API Reference

| Method             | Description                                                   |
|--------------------|---------------------------------------------------------------|
| `update()`         | Call repeatedly: returns `true` when time has elapsed         |
| `reset()`          | Cancels the current countdown                                 |
| `isRunning()`      | Returns `true` if the timer is active                         |
| `getDelay()`       | Returns the configured delay time in ms                       |
| `timeRemaining()`  | Milliseconds remaining until timeout                          |
| `timeElapsed()`    | Milliseconds elapsed since countdown start                    |

## 🧪 Basic Example

```cpp
#include <TonTime.h>
TonTime timer(false, 3000);

void loop() {
  timer.xStarted = digitalRead(2) == LOW;
  digitalWrite(13, timer.update());
}
```

## 📄 License

MIT License – developed by [AlexZappy](https://github.com/AlexZappy)
