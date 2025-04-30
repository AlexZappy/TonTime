# Contributing to TonTime

First off, thanks for taking the time to contribute! 🎉

Whether you’re filing an issue, proposing a feature, or opening a pull request, your help is greatly appreciated. Please follow these guidelines to make the process smooth for everyone.

---

## 1. Filing Issues

- Search existing issues before creating a new one to check for duplicates.
- When reporting a bug, include:
  - **Environment**: board (e.g. Arduino Uno R4 WiFi), PlatformIO/Arduino IDE version.
  - **TonTime version**: e.g. `2.0.0-beta`.
  - **Minimal reproducible example**: a short sketch demonstrating the problem.
  - **Expected** vs **actual** behavior.

## 2. Proposing Enhancements

- Open an issue first to discuss non-trivial changes.
- Clearly describe the **use case** and **benefits**.
- Avoid large scope changes without prior discussion.

## 3. Development Workflow

1. **Fork** the repository and **clone** your fork.
2. Create a **topic branch** off `develop`:

   ```bash
   git checkout develop
   git pull upstream develop
   git checkout -b feat/your-feature
   ```

3. Make your changes, adhering to the Coding Style below.
4. **Rebase** onto `develop` and **squash** commits when possible:

   ```bash
   git fetch upstream
   git rebase -i upstream/develop
   ```

5. Push your branch to your fork and open a **pull request** against `develop`.

## 4. Coding Style

Follow the existing style in this project for consistency:

- **Line length**: ≤80 characters.
- **Indentation**: 2 spaces (no tabs); 4 spaces for continuation lines.
- **Brace style**: opening brace on same line as control statement.
- **Naming**:
  - **Classes**: `CamelCase` (e.g. `TonTime`).
  - **Methods**: `lowerCamelCase` (e.g. `timeElapsed`).
  - **Constants**: `kCamelCase` (e.g. `kDefaultPreset`).
  - **Member variables**: `mCamelCase` (e.g. `mDelayTime`).
- **Doxygen**: document all public methods and non-trivial private methods.

## 5. Testing

This library provides two types of tests:

- **Native unit tests** (PlatformIO + Unity) in `test/`:
  - Run via `platformio test -e test_native`.
- **On-board self-tests** in `examples/SelfTest` using only TonTime; no external dependencies.

Please add test cases for any new functionality or bug fixes.

## 6. Examples and Documentation

- Place new Arduino example sketches under `examples/YourExampleName/` with a single `.ino` file.
- Update `README.md` to reference new examples and any changes to the API.
- Regenerate Doxygen docs and resolve any warnings.

## 7. License

All contributions must be released under the MIT License. Please include the standard MIT license header in any new source files.

---

Thanks again for helping improve TonTime! If you have any questions, feel free to open an issue or reach out.
