# Changelog

## Unreleased
- Custom scaling strategies: `appdimens_custom.h` (C99 single header, C++ compatible) ports `appdimens-dynamic` library-custom — shared JSON document, text formulas, code factors/formulas, rules, built-ins and presets; `adc_dp/adc_sp/adc_px`; `tests/test_custom.c` reproduces the 540-case cross-platform fixture.

## 3.2.0 — first release
- `AppDimens::Scope` (QObject) tracking QWindow/QWidget size, per-monitor fractional DPR, physical DPI, orientation, screen moves, Android/iOS split-screen.
- QML module `AppDimens 1.0`: singleton + `DimensScope`, 172 reactive factor properties, `dimen()`/`resolve()`/`styleSheet()`.
- Responsive Qt Style Sheets (`bindStyleSheet`), C++ literals, token cache.
- CMake + qmake, Qt 5 and Qt 6, tests (QtTest offscreen) and CI on Linux/Windows/macOS.
