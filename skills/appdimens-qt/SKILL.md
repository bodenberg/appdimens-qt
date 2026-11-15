---
name: appdimens-qt
description: Use for responsive sizing in Qt 5.12+/Qt 6 apps — QML/Qt Quick and Widgets on Windows, macOS, Linux, Android, iOS and embedded (eglfs) — whenever the user mentions appdimens-qt, AppDimens.sdp in QML, AppDimens::Scope, DimensScope, sdp/ssp in Qt style sheets, or HiDPI / multi-monitor sizing problems in Qt.
---

# appdimens-qt — workflow

1. Add the library (CMake `AppDimens::Qt` or `appdimens-qt.pri`); call `AppDimens::Scope::registerQmlTypes()` before loading QML.
2. QML: replace literal sizes with `value * AppDimens.<token>` (`sdp` default, `asdp`/`assp` for desktop/tablet/TV,
   `ftsdp` for canvases). Text: `font.pixelSize: 14 * AppDimens.ssp`. Multi-window apps: `DimensScope { target: win }`.
3. Widgets: `new AppDimens::Scope(&window, &window)`, `bindStyleSheet(widget, "…16sdp…")`, `px("8sdp")` for int setters,
   re-layout on `changed()`.
4. Don't multiply by devicePixelRatio (values are logical px); use `Px` tokens only for raw pixel buffers.
5. Validate at a 300 × 533 window (identity), a 1080p maximized window, a 4K @ 150 % monitor and after moving between monitors.
