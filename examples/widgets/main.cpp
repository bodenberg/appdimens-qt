// Widgets demo: resize the window or drag it to another monitor.
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "appdimens/appdimens_qt.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QWidget w;
    w.resize(400, 700);
    auto *lay = new QVBoxLayout(&w);
    auto *title = new QLabel("AppDimens for Qt");
    auto *info = new QLabel;
    auto *btn = new QPushButton("Continue");
    lay->addWidget(title);
    lay->addWidget(info);
    lay->addStretch();
    lay->addWidget(btn);
    auto *ad = new AppDimens::Scope(&w, &w);
    ad->bindStyleSheet(&w, "QLabel { font-size: 14assp; }"
                           "QPushButton { min-height: 44asdp; padding: 0 16sdp; font-size: 14assp; border-radius: 10sdp; }");
    ad->bindStyleSheet(title, "QLabel { font-size: 22assp; font-weight: bold; }");
    QObject::connect(ad, &AppDimens::Scope::changed, &w, [=] {
        lay->setContentsMargins(ad->px("16sdp"), ad->px("16sdp"), ad->px("16sdp"), ad->px("16sdp"));
        info->setText(QString("%1 × %2 · dpr %3 · 16sdp = %4 px")
                          .arg(ad->width()).arg(ad->height()).arg(ad->density()).arg(ad->dimen("16sdp")));
    });
    w.show();
    return app.exec();
}
