#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "appdimens/appdimens_qt.hpp"

int main(int argc, char **argv) {
    QGuiApplication app(argc, argv);
    AppDimens::Scope::registerQmlTypes();
    QQmlApplicationEngine engine(QUrl::fromLocalFile(QML_FILE));
    return app.exec();
}
