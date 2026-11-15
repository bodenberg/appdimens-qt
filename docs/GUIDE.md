# AppDimens Qt — guide

## Strategies by device class
| Device | Use |
|--------|-----|
| Phone-first app (Android/iOS) | `sdp` / `ssp` |
| Desktop app, tablets, TVs | `asdp` / `assp` (calm growth past 480 dp) |
| Car head units, ultrawide dashboards | `ftsdp` for content that must never crop; `sdpa` when aspect ratio matters |
| Kiosks / signage (very large) | `logsdp` |
| Embedded `eglfs`/`linuxfb` panels | `sdp` with `QT_SCALE_FACTOR` unset — the panel size drives scaling |

## High DPI
Qt 6 always enables high-DPI scaling; on Qt 5 call `QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling)` and
(5.14+) `QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough)` for
fractional factors. AppDimens values are logical px; use `Px` tokens (`resolve("sdpPx", v)`) only for QImage/OpenGL pixel work.

## Multi-monitor
Create one `Scope` (or `DimensScope`) per top-level window. Moving a window to another monitor emits `changed()` with
the new DPR/DPI.

## QML reactivity
`AppDimens.sdp(16)`, `ad.asdp(280)` and the helpers (`dimen`, `resolve`, `px`, `mm`, `styleSheet`) are QML functions that
read the scope's NOTIFY properties, so any binding that calls them re-evaluates when the window, screen or DPR changes.
The raw factors are NOTIFY properties too: `AppDimens.factors.sdp` (size = value × factor).

## Same API on every surface

| Where | Token applied to a value | Factor |
|-------|--------------------------|--------|
| QML (global) | `AppDimens.sdp(16)` | `AppDimens.factors.sdp` |
| QML (window) | `DimensScope { id: ad; target: win }` → `ad.sdp(16)` | `ad.factors.sdp` |
| C++ (window) | `ad->sdp(16)` | `ad->sdpFactor()` |
| C++ (global) | `AppDimens::sdp(16)` · `16_sdp` (`using namespace AppDimens::literals`) | `Scope::global()->sdpFactor()` |
| Style sheets / strings | `"padding: 16sdp"` (`bindStyleSheet`, `styleSheet`) | — |
