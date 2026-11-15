# qmake: include($$PWD/appdimens-qt/appdimens-qt.pri)
QT += core gui
qtHaveModule(widgets) { QT += widgets; DEFINES += APPDIMENS_QT_WIDGETS }
qtHaveModule(qml)     { QT += qml;     DEFINES += APPDIMENS_QT_QML; SOURCES += $$PWD/src/appdimens_qml.cpp }
CONFIG += c++17
INCLUDEPATH += $$PWD/include
HEADERS += $$PWD/include/appdimens/appdimens.h $$PWD/include/appdimens/appdimens_qt.hpp
SOURCES += $$PWD/src/appdimens_qt.cpp
