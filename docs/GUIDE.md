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
Factor properties (`AppDimens.sdp`) are NOTIFY properties. `AppDimens.dimen("16sdp")` is a function call: QML only
re-evaluates it if the binding also reads a property — e.g. `AppDimens.revision`.
