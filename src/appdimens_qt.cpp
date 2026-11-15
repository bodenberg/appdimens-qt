// AppDimens for Qt — implementation. Apache-2.0.
#include "appdimens/appdimens_qt.hpp"

#include <QCoreApplication>
#include <QEvent>
#include <QGuiApplication>
#include <QScreen>
#include <QWindow>
#include <cmath>
#include <cstring>
#include <utility>

#ifdef APPDIMENS_QT_WIDGETS
#include <QWidget>
#endif

namespace AppDimens {

// ── Style sheet expansion ──────────────────────────────────────────────────────────
static inline bool isIdent(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == '-';
}
static inline bool isDigit(char c) { return c >= '0' && c <= '9'; }
static inline bool isAlpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

QString expandStyleSheet(const ad_metrics &m, const QString &templ) {
    const QByteArray src = templ.toUtf8();
    const char *s = src.constData();
    const int n = src.size();
    QByteArray out;
    out.reserve(n + 64);
    int i = 0;
    bool inHex = false;
    while (i < n) {
        const char c = s[i];
        if (c == '#') { inHex = true; out.append(c); ++i; continue; }
        if (inHex && !isIdent(c)) inHex = false;
        const bool startsNumber = (isDigit(c) || (c == '.' && i + 1 < n && isDigit(s[i + 1]))) &&
                                  (i == 0 || !isIdent(s[i - 1]) || s[i - 1] == '-');
        if (!inHex && startsNumber) {
            int j = i;
            while (j < n && (isDigit(s[j]) || s[j] == '.')) ++j;
            int k = j;
            while (k < n && isAlpha(s[k])) ++k;
            if (k > j && (k >= n || !isIdent(s[k]))) {
                ad_token tok;
                const char *t = s + j;
                const size_t tl = size_t(k - j);
                const bool space = (tl == 6 && (!std::strncmp(t, "spaceW", 6) || !std::strncmp(t, "spaceH", 6))) ||
                                   (tl == 7 && !std::strncmp(t, "spaceSw", 7));
                if (space || ad_parse_token_n(t, tl, &tok)) {
                    ad_real v = 0;
                    size_t used = 0;
                    if (ad_dimen_n(&m, s + i, size_t(k - i), &v, &used) && int(used) == k - i) {
                        out.append(QByteArray::number(double(v), 'f', 2));
                        out.append("px");
                        i = k;
                        continue;
                    }
                }
            }
            out.append(s + i, k - i);
            i = k;
            continue;
        }
        out.append(c);
        ++i;
    }
    return QString::fromUtf8(out);
}

// ── Scope ──────────────────────────────────────────────────────────────────────────
Scope::Scope(QObject *parent) : QObject(parent) {
    ad_input in;
    ad_input_default(&in);
    ad_metrics_init(&m_m, &in);
}

Scope::Scope(QWindow *window, QObject *parent) : Scope(parent) { setTarget(window); }

#ifdef APPDIMENS_QT_WIDGETS
Scope::Scope(QWidget *widget, QObject *parent) : Scope(parent) { setTarget(static_cast<QObject *>(widget)); }
#endif

Scope::~Scope() {
    for (const auto &c : std::as_const(m_conns)) QObject::disconnect(c);
    for (const auto &c : std::as_const(m_screenConns)) QObject::disconnect(c);
}

Scope *Scope::global() {
    static QPointer<Scope> g;
    if (!g) {
        g = new Scope(QCoreApplication::instance());
        if (auto *app = qobject_cast<QGuiApplication *>(QCoreApplication::instance())) {
            Scope *self = g;
            auto pick = [self]() {
                if (self->m_target || self->m_manual) return;
                QWindow *w = QGuiApplication::focusWindow();
                if (!w) {
                    const auto tops = QGuiApplication::topLevelWindows();
                    for (QWindow *t : tops) if (t->isVisible()) { w = t; break; }
                }
                if (w) self->setTarget(w);
            };
            QObject::connect(app, &QGuiApplication::focusWindowChanged, g, pick);
            pick();
        }
    }
    return g;
}

QObject *Scope::target() const { return m_target; }

void Scope::setTarget(QObject *obj) {
    if (m_target == obj) return;
    if (m_target) m_target->removeEventFilter(this);
    if (m_window) m_window->removeEventFilter(this);
    for (const auto &c : std::as_const(m_conns)) QObject::disconnect(c);
    m_conns.clear();
    m_window = nullptr;
    m_target = obj;
    m_manual = false;
    if (obj) {
        obj->installEventFilter(this);
        if (auto *w = qobject_cast<QWindow *>(obj)) {
            attachWindow(w);
        }
#ifdef APPDIMENS_QT_WIDGETS
        else if (auto *wid = qobject_cast<QWidget *>(obj)) {
            if (QWidget *top = wid->window()) {
                if (top != wid) top->installEventFilter(this);
                if (top->windowHandle()) attachWindow(top->windowHandle());
            }
        }
#endif
        m_conns << connect(obj, &QObject::destroyed, this, [this]() { m_target = nullptr; m_window = nullptr; });
    }
    emit targetChanged();
    refresh();
}

void Scope::attachWindow(QWindow *w) {
    if (!w || m_window == w) return;
    if (m_window) m_window->removeEventFilter(this);
    m_window = w;
    if (w != m_target.data()) w->installEventFilter(this);
    m_conns << connect(w, &QWindow::widthChanged, this, [this]() { refresh(); });
    m_conns << connect(w, &QWindow::heightChanged, this, [this]() { refresh(); });
    m_conns << connect(w, &QWindow::screenChanged, this, [this](QScreen *s) { hookScreen(s); refresh(); });
    m_conns << connect(w, &QWindow::windowStateChanged, this, [this]() { refresh(); });
    hookScreen(w->screen());
}

void Scope::hookScreen(QScreen *s) {
    for (const auto &c : std::as_const(m_screenConns)) QObject::disconnect(c);
    m_screenConns.clear();
    m_screen = s;
    if (!s) return;
    auto r = [this]() { refresh(); };
    m_screenConns << connect(s, &QScreen::logicalDotsPerInchChanged, this, r);
    m_screenConns << connect(s, &QScreen::physicalDotsPerInchChanged, this, r);
    m_screenConns << connect(s, &QScreen::geometryChanged, this, r);
    m_screenConns << connect(s, &QScreen::orientationChanged, this, r);
}

bool Scope::eventFilter(QObject *o, QEvent *e) {
    switch (e->type()) {
    case QEvent::Resize:
    case QEvent::Show:
    case QEvent::ScreenChangeInternal:
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
    case QEvent::DevicePixelRatioChange:
#endif
    case QEvent::WindowStateChange:
#ifdef APPDIMENS_QT_WIDGETS
        if (!m_window) {
            if (auto *wid = qobject_cast<QWidget *>(m_target.data()))
                if (wid->window() && wid->window()->windowHandle()) attachWindow(wid->window()->windowHandle());
        }
#endif
        refresh();
        break;
    default:
        break;
    }
    return QObject::eventFilter(o, e);
}

ad_input Scope::read() const {
    ad_input in;
    ad_input_default(&in);
    in.ui_mode = m_ui;
    in.font_scale = ad_real(m_fontOverride > 0 ? m_fontOverride : 1.0);
    QWindow *w = m_window;
    QSize size;
#ifdef APPDIMENS_QT_WIDGETS
    if (auto *wid = qobject_cast<QWidget *>(m_target.data())) size = wid->size();
#endif
    if (!size.isValid() && w) size = w->size();
    QScreen *screen = w ? w->screen() : QGuiApplication::primaryScreen();
    if (!size.isValid() || size.isEmpty()) {
        if (!screen) return in;
        size = screen->availableGeometry().size();
    }
    in.width = ad_real(size.width());
    in.height = ad_real(size.height());
    const qreal dpr = w ? w->devicePixelRatio() : (screen ? screen->devicePixelRatio() : 1.0);
    in.density = ad_real(dpr > 0 ? dpr : 1.0);
    if (screen) {
        const QSizeF mm = screen->physicalSize();
        if (mm.width() > 0 && screen->geometry().width() > 0)
            in.dpi = ad_real(screen->geometry().width() * dpr / (mm.width() / 25.4));
    }
    if (m_mwSet) {
        in.multi_window = m_mwOverride ? 1 : 0;
    } else {
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
        // Split screen / slide-over / freeform: the window is clearly smaller than the screen.
        if (w && screen && !(w->windowStates() & (Qt::WindowFullScreen | Qt::WindowMaximized))) {
            const QRect a = screen->availableGeometry();
            in.multi_window = (size.width() < a.width() * 0.9 && size.height() < a.height() * 1.01) ||
                              (size.height() < a.height() * 0.9 && size.width() < a.width() * 1.01);
        }
#endif
    }
    return in;
}

bool Scope::refresh() {
    if (m_manual) return false;
    if (!m_target && !m_window) return false;
    return publish(read());
}

void Scope::setInput(const ad_input &in) {
    m_manual = true;
    publish(in);
}

bool Scope::publish(const ad_input &in) {
    ad_metrics next;
    ad_metrics_init(&next, &in);
    if (ad_metrics_same(&next, &m_m)) return false;
    next.generation = m_m.generation + 1;
    m_m = next;
    applyStyleSheets();
    emit changed();
    return true;
}

void Scope::setFontScale(qreal s) {
    m_fontOverride = s;
    ad_input in = m_manual ? m_m.in : read();
    in.font_scale = ad_real(s > 0 ? s : 1.0);
    publish(in);
}

void Scope::setMultiWindow(bool on) {
    m_mwSet = true;
    m_mwOverride = on;
    ad_input in = m_manual ? m_m.in : read();
    in.multi_window = on ? 1 : 0;
    publish(in);
}

void Scope::setUiMode(int mode) {
    m_ui = ad_ui_mode(mode);
    ad_input in = m_manual ? m_m.in : read();
    in.ui_mode = m_ui;
    publish(in);
}

qreal Scope::dimen(const QString &expr, qreal fallback) const {
    const QByteArray b = expr.toUtf8();
    ad_real v;
    return ad_dimen(&m_m, b.constData(), &v) ? qreal(v) : fallback;
}

int Scope::px(const QString &expr) const { return int(std::lround(dimen(expr, 0))); }

qreal Scope::resolve(const QString &token, qreal value) const {
    auto it = m_tokenCache.constFind(token);
    ad_token t;
    if (it == m_tokenCache.constEnd()) {
        const QByteArray b = token.toUtf8();
        if (!ad_parse_token(b.constData(), &t)) return value;
        m_tokenCache.insert(token, t);
    } else {
        t = *it;
    }
    return qreal(ad_token_resolve(&m_m, &t, ad_real(value)));
}

qreal Scope::factor(const QString &token) const { return resolve(token, 1.0); }

void Scope::bindStyleSheet(QWidget *w, const QString &templ) {
#ifdef APPDIMENS_QT_WIDGETS
    if (!w) return;
    if (!m_sheets.contains(w))
        connect(w, &QObject::destroyed, this, [this, w]() { m_sheets.remove(w); });
    m_sheets.insert(w, templ);
    w->setStyleSheet(expandStyleSheet(m_m, templ));
#else
    Q_UNUSED(w); Q_UNUSED(templ);
#endif
}

void Scope::unbindStyleSheet(QWidget *w) { m_sheets.remove(w); }

void Scope::applyStyleSheets() {
#ifdef APPDIMENS_QT_WIDGETS
    for (auto it = m_sheets.constBegin(); it != m_sheets.constEnd(); ++it)
        it.key()->setStyleSheet(expandStyleSheet(m_m, it.value()));
#endif
}

} // namespace AppDimens
