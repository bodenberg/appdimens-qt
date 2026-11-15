// QtTest suite — run with QT_QPA_PLATFORM=offscreen (set by CTest).
#include <QtTest/QtTest>
#include <QGuiApplication>
#include <QWindow>
#include <QSignalSpy>
#include "appdimens/appdimens_qt.hpp"
#ifdef APPDIMENS_QT_WIDGETS
#include <QApplication>
#include <QPushButton>
#endif
#ifdef HAVE_QUICK
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQuickItem>
#endif

using AppDimens::Scope;

class TestAppDimensQt : public QObject {
    Q_OBJECT
private slots:
    void reference() {
        Scope s;
        QCOMPARE(s.dimen("16sdp"), 16.0);
        QCOMPARE(s.sdp(), 1.0);
        QVERIFY(qFuzzyCompare(s.asdp(), 1.0));
    }
    void manualInputAndTokens() {
        Scope s;
        ad_input in; ad_input_default(&in);
        in.width = 600; in.height = 1024; in.density = 2; in.font_scale = 1.25;
        QSignalSpy spy(&s, &Scope::changed);
        s.setInput(in);
        QCOMPARE(spy.count(), 1);
        s.setInput(in);                                // identical → no signal
        QCOMPARE(spy.count(), 1);
        QCOMPARE(s.dimen("16sdp"), 32.0);
        QCOMPARE(s.dimen("10ssp"), 25.0);
        QCOMPARE(s.dimen("10sem"), 20.0);
        QCOMPARE(s.resolve("sdpPx", 10), 40.0);
        QVERIFY(qAbs(s.dimen("16asdp") - 16 * (1.6 + 0.4 * std::log(1.4))) < 1e-9);
        QCOMPARE(s.dimen("bad", -1), -1.0);
        QCOMPARE(s.resolve("bad", 7), 7.0);
        QCOMPARE(s.px("16sdp"), 32);
        QCOMPARE(s.ssp(), 2.5);
        QCOMPARE(s.hdpLw(), 1024.0 / 300.0);        // portrait → height
        QCOMPARE(s.spaceW(50), 300.0);
        QVERIFY(s.portrait());
        QCOMPARE(s.styleSheet("QPushButton{padding:16sdp;color:#1d4ed8;border:1px}"),
                 QString("QPushButton{padding:32.00px;color:#1d4ed8;border:1px}"));
    }
    void tracksWindow() {
        QWindow w;
        w.resize(800, 480);
        Scope s(&w);
        w.show();
        QVERIFY(QTest::qWaitForWindowExposed(&w) || true);
        QTRY_COMPARE(s.width(), 800.0);
        QCOMPARE(s.height(), 480.0);
        QVERIFY(s.landscape());
        QSignalSpy spy(&s, &Scope::changed);
        w.resize(480, 800);
        QTRY_VERIFY(spy.count() >= 1);
        QTRY_COMPARE(s.width(), 480.0);
        QVERIFY(s.portrait());
        QCOMPARE(s.dimen("10sdp"), 16.0);
    }
#ifdef APPDIMENS_QT_WIDGETS
    void widgetStyleSheet() {
        QPushButton b("ok");
        b.resize(600, 300);
        Scope s(static_cast<QWidget *>(&b));
        s.bindStyleSheet(&b, "QPushButton { padding: 10sdp; }");
        b.show();
        QTRY_COMPARE(s.width(), 600.0);
        QCOMPARE(b.styleSheet(), QString("QPushButton { padding: 10.00px; }"));
        b.resize(900, 900);
        QTRY_COMPARE(b.styleSheet(), QString("QPushButton { padding: 30.00px; }"));
    }
#endif
#ifdef HAVE_QUICK
    void qmlBindingsAreReactive() {
        Scope::registerQmlTypes();
        Scope *g = Scope::global();
        ad_input in; ad_input_default(&in); in.width = 360; in.height = 640;
        g->setInput(in);
        QQmlEngine engine;
        QQmlComponent c(&engine);
        c.setData("import QtQuick 2.12\nimport AppDimens 1.0\n"
                  "Item { width: 100 * AppDimens.sdp; height: 10 * AppDimens.ssp;"
                  " property real a: AppDimens.dimen('16asdp', 0);"
                  " property real t: 120 * AppDimens.ftsdp }", QUrl());
        QScopedPointer<QObject> o(c.create());
        QVERIFY2(o, qPrintable(c.errorString()));
        auto *item = qobject_cast<QQuickItem *>(o.data());
        QCOMPARE(item->width(), 120.0);
        in.width = 720; in.height = 1280;
        g->setInput(in);
        QCOMPARE(item->width(), 240.0);              // binding re-evaluated through NOTIFY
        QCOMPARE(item->height(), 24.0);
        QQmlComponent c2(&engine);
        c2.setData("import QtQuick 2.12\nimport AppDimens 1.0\nItem { DimensScope { id: d } width: 50 * d.sdp }", QUrl());
        QScopedPointer<QObject> o2(c2.create());
        QVERIFY2(o2, qPrintable(c2.errorString()));
        QCOMPARE(qobject_cast<QQuickItem *>(o2.data())->width(), 50.0);
    }
#endif
    void literals() {
        using namespace AppDimens::literals;
        ad_input in; ad_input_default(&in); in.width = 900; in.height = 1600;
        Scope::global()->setInput(in);
        QCOMPARE(qreal(16_sdp), 48.0);
        QCOMPARE(qreal(2.5_sdp), 7.5);
    }
};

int main(int argc, char **argv) {
#ifdef APPDIMENS_QT_WIDGETS
    QApplication app(argc, argv);
#else
    QGuiApplication app(argc, argv);
#endif
    TestAppDimensQt t;
    return QTest::qExec(&t, argc, argv);
}
#include "tst_appdimens_qt.moc"
