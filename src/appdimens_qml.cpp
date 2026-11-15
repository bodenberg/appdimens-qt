// QML registration: singleton `AppDimens` (global scope) and creatable `DimensScope`.
#include "appdimens/appdimens_qt.hpp"

#include <QQmlEngine>

namespace AppDimens {

void Scope::registerQmlTypes(const char *uri) {
    qmlRegisterSingletonType<Scope>(uri, 1, 0, "AppDimens", [](QQmlEngine *, QJSEngine *) -> QObject * {
        Scope *g = Scope::global();
        QQmlEngine::setObjectOwnership(g, QQmlEngine::CppOwnership);
        return g;
    });
    qmlRegisterType<Scope>(uri, 1, 0, "DimensScope");
}

} // namespace AppDimens
