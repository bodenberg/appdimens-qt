# Changelog

## 3.2.0 — first release
- `AppDimens::Scope` (QObject) tracking QWindow/QWidget size, per-monitor fractional DPR, physical DPI, orientation, screen moves, Android/iOS split-screen.
- QML module `AppDimens 1.0`: singleton + `DimensScope`, 172 reactive factor properties, `dimen()`/`resolve()`/`styleSheet()`.
- Responsive Qt Style Sheets (`bindStyleSheet`), C++ literals, token cache.
- CMake + qmake, Qt 5 and Qt 6, tests (QtTest offscreen) and CI on Linux/Windows/macOS.
