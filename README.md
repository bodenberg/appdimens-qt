<div align="center">

# AppDimens for Qt

**Write `AppDimens.sdp(16)` once — the same token as `16.sdp` on Android, iOS and Flutter or `sdp(16)` on the Web. It looks right on a phone, a tablet, a 4K monitor at 150 %, a car head unit, a kiosk or an embedded `eglfs` panel — and it follows the window across monitors.**

[![Release](https://img.shields.io/badge/release-3.2.0-1d4ed8.svg)](CHANGELOG.md)
[![Qt](https://img.shields.io/badge/Qt-5.12%2B%20%7C%206.x-15803d.svg)](#install)
[![Platforms](https://img.shields.io/badge/platforms-Windows%20%7C%20macOS%20%7C%20Linux%20%7C%20Android%20%7C%20iOS%20%7C%20embedded-f59e0b.svg)](#where-values-come-from)
[![License](https://img.shields.io/badge/license-Apache%202.0-15803d.svg)](LICENSE)

Part of the [AppDimens family](https://github.com/bodenberg/appdimens) — same tokens and math as Android, iOS, Flutter, React Native, Web, .NET, GTK, LVGL, Roku, Python and Games.

🇧🇷 [Resumo em português](#-resumo-em-português)

</div>

## Install

CMake (`add_subdirectory(appdimens-qt)` → `AppDimens::Qt`, or `find_package(AppDimensQt)` after install) or qmake
(`include(appdimens-qt/appdimens-qt.pri)`). Builds against Qt 5.12+ and Qt 6.x; Widgets and QML are enabled when present.

## QML

```qml
import AppDimens 1.0          // after AppDimens::Scope::registerQmlTypes() in main()

Rectangle {
    width: AppDimens.asdp(280);  height: AppDimens.sdp(56)
    radius: AppDimens.sdp(12)
    Text { font.pixelSize: AppDimens.ssp(14) }
}

Window { id: win; DimensScope { id: ad; target: win }   // per-window scope (multi-monitor)
         Item { width: ad.sdp(120) } }
```

Every family token is a function applied to a value, exactly like the other AppDimens libraries — 172 of them: `sdp hdp
wdp ssp sem asdp assp ftsdp flsdp pwsdp logsdp dgsdp prsdp fsdp isdp psdp dsdp`, the `a`/`i` variants and the
`Ph/Lh/Pw/Lw` inverters. They are **reactive**: a binding such as `width: AppDimens.sdp(120)` re-evaluates when the window,
screen or DPR changes. Also `dimen("16sdp")`, `resolve("sdpPh", 16)`, `spaceW(50)`, `mm(5)`, `styleSheet(...)` (reactive
too) and the raw factors as properties: `AppDimens.factors.sdp`.

## Widgets

```cpp
auto *ad = new AppDimens::Scope(&window, &window);
ad->bindStyleSheet(&window, "QPushButton { min-height: 44asdp; padding: 0 16sdp; font-size: 14assp; }");
layout->setSpacing(ad->px("8sdp"));
connect(ad, &AppDimens::Scope::changed, &window, relayout);

qreal gap = ad->asdp(24);               // the token applied to a value (this window)
qreal pad = AppDimens::sdp(16);         // global scope (the first window shown)
using namespace AppDimens::literals;    // literals over the global scope: 16_sdp, 14_ssp, 120_ftsdp …
qreal title = 20_assp;
const ad_metrics &m = ad->metrics();    // core hot path: ad_sdp(&m, 16), ad_ftsdp_px(&m, 24)
```

## Where values come from

| Input | Source |
|-------|--------|
| width/height | `QWidget::size()` / `QWindow::size()` (logical px) |
| density | `QWindow::devicePixelRatio()` — per monitor, fractional (Qt ≥ 5.14 rounding policy / Qt 6) |
| dpi | `QScreen::geometry × dpr ÷ physicalSize` |
| orientation | window shape (follows `QScreen::orientationChanged`, rotation on Android/iOS/eglfs) |
| multi-window | Android split-screen / iPad Slide Over heuristic, or `setMultiWindow()` |
| font scale | `setFontScale()` (bind to your accessibility setting) |
| UI mode | `setUiMode(AD_UI_TELEVISION / AD_UI_CAR / AD_UI_APPLIANCE …)` |

Updates are signal/event driven (resize, screen change, DPR change, screen DPI/geometry/orientation) — no polling;
identical snapshots don't emit `changed()`.

## Custom strategies

Your own scaling rule, shared with every AppDimens platform (same JSON document and text formulas),
through the C99 single header `appdimens_custom.h`:

```c
#define ADC_IMPLEMENTATION
#include "appdimens/appdimens_custom.h"
adc_load_json(json_text, err, sizeof err);                       /* ids + "default" */
float pad = adc_dp(adc_get("brand"), &AppDimens::Scope::global()->metrics(), 16);
adc_strategy *hud = adc_formula("base * pow(sw / 360, 0.8)", err, sizeof err);
```

Reproduces the cross-platform 540-case fixture. Details: [docs/CUSTOM.md](docs/CUSTOM.md).

## Precision and performance

- Core parity: 10 704 checks against reference vectors (float/double/no-libm/fixed point) — `tests/test_core.c`.
- Qt suite (`tests/tst_appdimens_qt.cpp`): tokens, window tracking, rotation, widget style sheets, reactive QML
  bindings, literals — passing on Qt 5.15 and Qt 6.4+ (offscreen).
- A token is one table load and one multiply; `resolve()` caches parsed tokens.

Docs: [Guide](docs/GUIDE.md) · [Skill](skills/appdimens-qt/SKILL.md) · [LLMS.txt](LLMS.txt)

<!-- appdimens-family:begin (maintained in bodenberg/appdimens tools/family_block.py) -->
## 🌍 AppDimens family

Same token names and the same math on every platform — [hub](https://github.com/bodenberg/appdimens) · [AI agent skills](https://github.com/bodenberg/appdimens-skills) · [custom strategies](https://github.com/bodenberg/appdimens/blob/main/DOCS/CUSTOM.md) (one JSON for every platform).

| Platform | Library | Scaled `16` |
|---|---|---|
| Android — Jetpack Compose, Views, Java | [appdimens-dynamic](https://github.com/bodenberg/appdimens-dynamic) | `16.sdp` · `16.sdp(context)` |
| Android — XML resources | [appdimens-sdps](https://github.com/bodenberg/appdimens-sdps) | `@dimen/_16sdp` |
| Android — XML text sizes | [appdimens-ssps](https://github.com/bodenberg/appdimens-ssps) | `@dimen/_16ssp` |
| Kotlin / Compose Multiplatform | [appdimens-kmp](https://github.com/bodenberg/appdimens-kmp) | `16.sdp` |
| iOS · macOS — SwiftUI, UIKit, AppKit, Metal | [appdimens-ios](https://github.com/bodenberg/appdimens-ios) | `16.sdp` |
| Flutter | [appdimens-flutter](https://github.com/bodenberg/appdimens-flutter) | `16.sdp` |
| React Native / Expo | [appdimens-react-native](https://github.com/bodenberg/appdimens-react-native) | `sdp(16)` |
| Web — HTML/CSS, React, Vue, Svelte, Angular | [appdimens-web](https://github.com/bodenberg/appdimens-web) | `sdp(16)` · `16sdp` |
| .NET — MAUI, WPF, WinForms, WinUI, Android | [appdimens-net-binding](https://github.com/bodenberg/appdimens-net-binding) | `16.Sdp()` · `{sdp:16}` |
| Qt 5/6 — QML, Widgets | **appdimens-qt** (this repository) | `AppDimens.sdp(16)` · `16_sdp` |
| GTK 3/4 and portable C99 | [appdimens-gtk](https://github.com/bodenberg/appdimens-gtk) | `16sdp` (CSS) · `ad_sdp(&m, 16)` |
| LVGL 8/9 — MCUs, embedded Linux | [appdimens-lvgl](https://github.com/bodenberg/appdimens-lvgl) | `lv_ad_sdp(16)` |
| Roku — BrightScript / SceneGraph | [appdimens-roku](https://github.com/bodenberg/appdimens-roku) | `sdp(16)` · `ad.sdp(16)` |
| Python — Tkinter, Qt, Kivy, pygame, Blender | [appdimens-py](https://github.com/bodenberg/appdimens-py) | `ad.sdp(16)` |
| Games — Unity, Unreal, Godot, C/C++, .NET, Android | [appdimens-games](https://github.com/bodenberg/appdimens-games) | `64f.ASdp()` · `AppDimens.asdp(64)` · `appdimens::asdp(64)` |

<!-- appdimens-family:end -->

## 🇧🇷 Resumo em português

**AppDimens para Qt** (Qt 5.12+ e Qt 6, Widgets e QML, Windows/macOS/Linux/Android/iOS/embarcado). No QML use
`width: AppDimens.sdp(120)` e `font.pixelSize: AppDimens.ssp(14)` (o mesmo padrão `16.sdp` / `sdp(16)` da família); em C++ `ad->sdp(16)`, `AppDimens::sdp(16)` ou `16_sdp`; em Widgets use `bindStyleSheet(w, "padding: 16sdp")`.
Acompanha o tamanho da janela, o devicePixelRatio de cada monitor (inclusive fracionário), o DPI, a rotação e a troca de
monitor, sem polling.

## Author

**Jean Bodenberg** — [@bodenberg](https://github.com/bodenberg) · Apache 2.0
