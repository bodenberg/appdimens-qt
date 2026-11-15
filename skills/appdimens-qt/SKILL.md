---
name: appdimens-qt
description: Use for responsive sizing in Qt 5.12+/Qt 6 apps — QML/Qt Quick and Widgets on Windows, macOS, Linux, Android, iOS and embedded (eglfs) — whenever the user mentions appdimens-qt, AppDimens.sdp(16) in QML, AppDimens::Scope, DimensScope, sdp/ssp in Qt style sheets, or HiDPI / multi-monitor sizing problems in Qt.
---

# appdimens-qt — workflow

1. Add the library (CMake `AppDimens::Qt` or `appdimens-qt.pri`); call `AppDimens::Scope::registerQmlTypes()` before loading QML.
2. QML: replace literal sizes with `AppDimens.<token>(value)` — `AppDimens.sdp(16)` (`sdp` default, `asdp`/`assp` for
   desktop/tablet/TV, `ftsdp` for canvases); reactive in bindings. Text: `font.pixelSize: AppDimens.ssp(14)`.
   Multi-window apps: `DimensScope { id: ad; target: win }` → `ad.sdp(16)`. Never write `16 * AppDimens.sdp` (the old
   factor form); raw factors are `AppDimens.factors.sdp`.
   C++: `ad->sdp(16)`, `AppDimens::sdp(16)` (global scope) or `16_sdp` literals.
3. Widgets: `new AppDimens::Scope(&window, &window)`, `bindStyleSheet(widget, "…16sdp…")`, `px("8sdp")` for int setters,
   re-layout on `changed()`.
4. Don't multiply by devicePixelRatio (values are logical px); use `Px` tokens only for raw pixel buffers.
5. Validate at a 300 × 533 window (identity), a 1080p maximized window, a 4K @ 150 % monitor and after moving between monitors.

## Custom strategies

Only when the project declares `customStrategies` (or the user asks for their own rule): one
`#define ADC_IMPLEMENTATION` + `#include "appdimens/appdimens_custom.h"`, `adc_load_json(text, err, n)` at start-up, then
`adc_dp(adc_get("brand"), &AppDimens::Scope::global()->metrics(), 16)` / `adc_sp(...)`. One-off math: `adc_formula("base * pow(sw / 360, 0.8)", err, n)`. Never invent
ids; not available in `AD_FIXED_POINT` builds. Reference: `docs/CUSTOM.md`.

<!-- appdimens-family:begin -->
## Other AppDimens platforms

The same token names and math exist on Android (Compose, Views, XML), Kotlin Multiplatform, iOS/macOS, Flutter, React
Native, Web, .NET, Qt, GTK, LVGL, Roku, Python/Blender and games (Unity, Unreal, Godot, C/C++). For code on another
platform, use that library's skill — every skill, plus the layout-intent decision table, installs with
`npx appdimens-skills` (https://github.com/bodenberg/appdimens-skills). Hub: https://github.com/bodenberg/appdimens.
<!-- appdimens-family:end -->
