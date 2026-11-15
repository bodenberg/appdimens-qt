// qmake integration check: appdimens-qt.pri + the QML module (AppDimens.sdp(100) at 600 dp = 200).
#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickItem>
#include "appdimens/appdimens_qt.hpp"
int main(int c, char **v) {
    QGuiApplication app(c, v);
    AppDimens::Scope::registerQmlTypes();
    ad_input in; ad_input_default(&in); in.width = 600; in.height = 900;
    AppDimens::Scope::global()->setInput(in);
    QQmlEngine e; QQmlComponent k(&e);
    k.setData("import QtQuick 2.12\nimport AppDimens 1.0\nItem { width: AppDimens.sdp(100) }", QUrl());
    QObject *o = k.create();
    if (!o) { qWarning() << k.errorString(); return 1; }
    printf("qmake width=%g\n", qobject_cast<QQuickItem *>(o)->width());
    return qobject_cast<QQuickItem *>(o)->width() == 200 ? 0 : 1;
}
