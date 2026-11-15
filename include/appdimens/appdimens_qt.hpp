// AppDimens for Qt 5.12+ and Qt 6 — Widgets, QML/Qt Quick, desktop, Android, iOS, embedded.
// Version 3.2.0 · Apache-2.0 · https://github.com/bodenberg/appdimens-qt
//
//   QML:      width: 120 * AppDimens.sdp;  font.pixelSize: 14 * AppDimens.ssp
//   Widgets:  auto *ad = new AppDimens::Scope(window); ad->bindStyleSheet(w, "QPushButton{padding:8sdp;font-size:14ssp}");
//   C++:      ad->dimen("16asdp");  ad->resolve("sdpPh", 16);  ad_sdp(&ad->metrics(), 16);
//   Literals: using namespace AppDimens::literals;  int pad = 16_sdp;   // global scope
//
// Each Scope tracks one QWindow / QWidget: logical size, per-monitor devicePixelRatio
// (fractional on Qt ≥ 5.14/6), physical DPI, screen orientation and moves between screens.
#pragma once

#ifndef AD_USE_DOUBLE
#define AD_USE_DOUBLE   // qreal precision
#endif
#include "appdimens.h"

#include <QObject>
#include <QPointer>
#include <QString>
#include <QVector>
#include <QHash>

class QWindow;
class QWidget;
class QScreen;
class QQmlEngine;
class QJSEngine;

namespace AppDimens {

/// Version of this binding.
inline constexpr const char *version() { return AD_VERSION_STRING; }

/// Expands AppDimens tokens ("16sdp", "14ssp", "50spaceW") inside any text — Qt Style
/// Sheets, QML strings, HTML — to "<n>px". Plain units, hex colours and identifiers stay.
QString expandStyleSheet(const ad_metrics &m, const QString &templ);

class Scope : public QObject {
    Q_OBJECT
    Q_PROPERTY(qreal width READ width NOTIFY changed)
    Q_PROPERTY(qreal height READ height NOTIFY changed)
    Q_PROPERTY(qreal smallestWidth READ smallestWidth NOTIFY changed)
    Q_PROPERTY(qreal density READ density NOTIFY changed)
    Q_PROPERTY(qreal fontScale READ fontScale WRITE setFontScale NOTIFY changed)
    Q_PROPERTY(qreal dpi READ dpi NOTIFY changed)
    Q_PROPERTY(bool landscape READ landscape NOTIFY changed)
    Q_PROPERTY(bool portrait READ portrait NOTIFY changed)
    Q_PROPERTY(bool multiWindow READ multiWindow WRITE setMultiWindow NOTIFY changed)
    Q_PROPERTY(int uiMode READ uiMode WRITE setUiMode NOTIFY changed)
    Q_PROPERTY(quint32 revision READ revision NOTIFY changed)
    Q_PROPERTY(QObject *target READ target WRITE setTarget NOTIFY targetChanged)
    // <generated> by tools/gen_properties.py — do not edit by hand
    Q_PROPERTY(qreal sdp READ sdp NOTIFY changed)
    Q_PROPERTY(qreal ssp READ ssp NOTIFY changed)
    Q_PROPERTY(qreal sdpa READ sdpa NOTIFY changed)
    Q_PROPERTY(qreal sdpi READ sdpi NOTIFY changed)
    Q_PROPERTY(qreal hdp READ hdp NOTIFY changed)
    Q_PROPERTY(qreal hsp READ hsp NOTIFY changed)
    Q_PROPERTY(qreal hdpa READ hdpa NOTIFY changed)
    Q_PROPERTY(qreal hdpi READ hdpi NOTIFY changed)
    Q_PROPERTY(qreal wdp READ wdp NOTIFY changed)
    Q_PROPERTY(qreal wsp READ wsp NOTIFY changed)
    Q_PROPERTY(qreal wdpa READ wdpa NOTIFY changed)
    Q_PROPERTY(qreal wdpi READ wdpi NOTIFY changed)
    Q_PROPERTY(qreal asdp READ asdp NOTIFY changed)
    Q_PROPERTY(qreal assp READ assp NOTIFY changed)
    Q_PROPERTY(qreal asdpa READ asdpa NOTIFY changed)
    Q_PROPERTY(qreal asdpi READ asdpi NOTIFY changed)
    Q_PROPERTY(qreal ahdp READ ahdp NOTIFY changed)
    Q_PROPERTY(qreal ahsp READ ahsp NOTIFY changed)
    Q_PROPERTY(qreal ahdpa READ ahdpa NOTIFY changed)
    Q_PROPERTY(qreal ahdpi READ ahdpi NOTIFY changed)
    Q_PROPERTY(qreal awdp READ awdp NOTIFY changed)
    Q_PROPERTY(qreal awsp READ awsp NOTIFY changed)
    Q_PROPERTY(qreal awdpa READ awdpa NOTIFY changed)
    Q_PROPERTY(qreal awdpi READ awdpi NOTIFY changed)
    Q_PROPERTY(qreal psdp READ psdp NOTIFY changed)
    Q_PROPERTY(qreal pssp READ pssp NOTIFY changed)
    Q_PROPERTY(qreal psdpa READ psdpa NOTIFY changed)
    Q_PROPERTY(qreal psdpi READ psdpi NOTIFY changed)
    Q_PROPERTY(qreal phdp READ phdp NOTIFY changed)
    Q_PROPERTY(qreal phsp READ phsp NOTIFY changed)
    Q_PROPERTY(qreal phdpa READ phdpa NOTIFY changed)
    Q_PROPERTY(qreal phdpi READ phdpi NOTIFY changed)
    Q_PROPERTY(qreal pwdp READ pwdp NOTIFY changed)
    Q_PROPERTY(qreal pwsp READ pwsp NOTIFY changed)
    Q_PROPERTY(qreal pwdpa READ pwdpa NOTIFY changed)
    Q_PROPERTY(qreal pwdpi READ pwdpi NOTIFY changed)
    Q_PROPERTY(qreal pwsdp READ pwsdp NOTIFY changed)
    Q_PROPERTY(qreal pwssp READ pwssp NOTIFY changed)
    Q_PROPERTY(qreal pwsdpa READ pwsdpa NOTIFY changed)
    Q_PROPERTY(qreal pwsdpi READ pwsdpi NOTIFY changed)
    Q_PROPERTY(qreal pwhdp READ pwhdp NOTIFY changed)
    Q_PROPERTY(qreal pwhsp READ pwhsp NOTIFY changed)
    Q_PROPERTY(qreal pwhdpa READ pwhdpa NOTIFY changed)
    Q_PROPERTY(qreal pwhdpi READ pwhdpi NOTIFY changed)
    Q_PROPERTY(qreal pwwdp READ pwwdp NOTIFY changed)
    Q_PROPERTY(qreal pwwsp READ pwwsp NOTIFY changed)
    Q_PROPERTY(qreal pwwdpa READ pwwdpa NOTIFY changed)
    Q_PROPERTY(qreal pwwdpi READ pwwdpi NOTIFY changed)
    Q_PROPERTY(qreal fsdp READ fsdp NOTIFY changed)
    Q_PROPERTY(qreal fssp READ fssp NOTIFY changed)
    Q_PROPERTY(qreal fsdpa READ fsdpa NOTIFY changed)
    Q_PROPERTY(qreal fsdpi READ fsdpi NOTIFY changed)
    Q_PROPERTY(qreal fhdp READ fhdp NOTIFY changed)
    Q_PROPERTY(qreal fhsp READ fhsp NOTIFY changed)
    Q_PROPERTY(qreal fhdpa READ fhdpa NOTIFY changed)
    Q_PROPERTY(qreal fhdpi READ fhdpi NOTIFY changed)
    Q_PROPERTY(qreal fwdp READ fwdp NOTIFY changed)
    Q_PROPERTY(qreal fwsp READ fwsp NOTIFY changed)
    Q_PROPERTY(qreal fwdpa READ fwdpa NOTIFY changed)
    Q_PROPERTY(qreal fwdpi READ fwdpi NOTIFY changed)
    Q_PROPERTY(qreal isdp READ isdp NOTIFY changed)
    Q_PROPERTY(qreal issp READ issp NOTIFY changed)
    Q_PROPERTY(qreal isdpa READ isdpa NOTIFY changed)
    Q_PROPERTY(qreal isdpi READ isdpi NOTIFY changed)
    Q_PROPERTY(qreal ihdp READ ihdp NOTIFY changed)
    Q_PROPERTY(qreal ihsp READ ihsp NOTIFY changed)
    Q_PROPERTY(qreal ihdpa READ ihdpa NOTIFY changed)
    Q_PROPERTY(qreal ihdpi READ ihdpi NOTIFY changed)
    Q_PROPERTY(qreal iwdp READ iwdp NOTIFY changed)
    Q_PROPERTY(qreal iwsp READ iwsp NOTIFY changed)
    Q_PROPERTY(qreal iwdpa READ iwdpa NOTIFY changed)
    Q_PROPERTY(qreal iwdpi READ iwdpi NOTIFY changed)
    Q_PROPERTY(qreal logsdp READ logsdp NOTIFY changed)
    Q_PROPERTY(qreal logssp READ logssp NOTIFY changed)
    Q_PROPERTY(qreal logsdpa READ logsdpa NOTIFY changed)
    Q_PROPERTY(qreal logsdpi READ logsdpi NOTIFY changed)
    Q_PROPERTY(qreal loghdp READ loghdp NOTIFY changed)
    Q_PROPERTY(qreal loghsp READ loghsp NOTIFY changed)
    Q_PROPERTY(qreal loghdpa READ loghdpa NOTIFY changed)
    Q_PROPERTY(qreal loghdpi READ loghdpi NOTIFY changed)
    Q_PROPERTY(qreal logwdp READ logwdp NOTIFY changed)
    Q_PROPERTY(qreal logwsp READ logwsp NOTIFY changed)
    Q_PROPERTY(qreal logwdpa READ logwdpa NOTIFY changed)
    Q_PROPERTY(qreal logwdpi READ logwdpi NOTIFY changed)
    Q_PROPERTY(qreal dgsdp READ dgsdp NOTIFY changed)
    Q_PROPERTY(qreal dgssp READ dgssp NOTIFY changed)
    Q_PROPERTY(qreal dgsdpa READ dgsdpa NOTIFY changed)
    Q_PROPERTY(qreal dgsdpi READ dgsdpi NOTIFY changed)
    Q_PROPERTY(qreal dghdp READ dghdp NOTIFY changed)
    Q_PROPERTY(qreal dghsp READ dghsp NOTIFY changed)
    Q_PROPERTY(qreal dghdpa READ dghdpa NOTIFY changed)
    Q_PROPERTY(qreal dghdpi READ dghdpi NOTIFY changed)
    Q_PROPERTY(qreal dgwdp READ dgwdp NOTIFY changed)
    Q_PROPERTY(qreal dgwsp READ dgwsp NOTIFY changed)
    Q_PROPERTY(qreal dgwdpa READ dgwdpa NOTIFY changed)
    Q_PROPERTY(qreal dgwdpi READ dgwdpi NOTIFY changed)
    Q_PROPERTY(qreal prsdp READ prsdp NOTIFY changed)
    Q_PROPERTY(qreal prssp READ prssp NOTIFY changed)
    Q_PROPERTY(qreal prsdpa READ prsdpa NOTIFY changed)
    Q_PROPERTY(qreal prsdpi READ prsdpi NOTIFY changed)
    Q_PROPERTY(qreal prhdp READ prhdp NOTIFY changed)
    Q_PROPERTY(qreal prhsp READ prhsp NOTIFY changed)
    Q_PROPERTY(qreal prhdpa READ prhdpa NOTIFY changed)
    Q_PROPERTY(qreal prhdpi READ prhdpi NOTIFY changed)
    Q_PROPERTY(qreal prwdp READ prwdp NOTIFY changed)
    Q_PROPERTY(qreal prwsp READ prwsp NOTIFY changed)
    Q_PROPERTY(qreal prwdpa READ prwdpa NOTIFY changed)
    Q_PROPERTY(qreal prwdpi READ prwdpi NOTIFY changed)
    Q_PROPERTY(qreal ftsdp READ ftsdp NOTIFY changed)
    Q_PROPERTY(qreal ftssp READ ftssp NOTIFY changed)
    Q_PROPERTY(qreal ftsdpa READ ftsdpa NOTIFY changed)
    Q_PROPERTY(qreal ftsdpi READ ftsdpi NOTIFY changed)
    Q_PROPERTY(qreal fthdp READ fthdp NOTIFY changed)
    Q_PROPERTY(qreal fthsp READ fthsp NOTIFY changed)
    Q_PROPERTY(qreal fthdpa READ fthdpa NOTIFY changed)
    Q_PROPERTY(qreal fthdpi READ fthdpi NOTIFY changed)
    Q_PROPERTY(qreal ftwdp READ ftwdp NOTIFY changed)
    Q_PROPERTY(qreal ftwsp READ ftwsp NOTIFY changed)
    Q_PROPERTY(qreal ftwdpa READ ftwdpa NOTIFY changed)
    Q_PROPERTY(qreal ftwdpi READ ftwdpi NOTIFY changed)
    Q_PROPERTY(qreal flsdp READ flsdp NOTIFY changed)
    Q_PROPERTY(qreal flssp READ flssp NOTIFY changed)
    Q_PROPERTY(qreal flsdpa READ flsdpa NOTIFY changed)
    Q_PROPERTY(qreal flsdpi READ flsdpi NOTIFY changed)
    Q_PROPERTY(qreal flhdp READ flhdp NOTIFY changed)
    Q_PROPERTY(qreal flhsp READ flhsp NOTIFY changed)
    Q_PROPERTY(qreal flhdpa READ flhdpa NOTIFY changed)
    Q_PROPERTY(qreal flhdpi READ flhdpi NOTIFY changed)
    Q_PROPERTY(qreal flwdp READ flwdp NOTIFY changed)
    Q_PROPERTY(qreal flwsp READ flwsp NOTIFY changed)
    Q_PROPERTY(qreal flwdpa READ flwdpa NOTIFY changed)
    Q_PROPERTY(qreal flwdpi READ flwdpi NOTIFY changed)
    Q_PROPERTY(qreal dsdp READ dsdp NOTIFY changed)
    Q_PROPERTY(qreal dssp READ dssp NOTIFY changed)
    Q_PROPERTY(qreal dsdpa READ dsdpa NOTIFY changed)
    Q_PROPERTY(qreal dsdpi READ dsdpi NOTIFY changed)
    Q_PROPERTY(qreal dhdp READ dhdp NOTIFY changed)
    Q_PROPERTY(qreal dhsp READ dhsp NOTIFY changed)
    Q_PROPERTY(qreal dhdpa READ dhdpa NOTIFY changed)
    Q_PROPERTY(qreal dhdpi READ dhdpi NOTIFY changed)
    Q_PROPERTY(qreal dwdp READ dwdp NOTIFY changed)
    Q_PROPERTY(qreal dwsp READ dwsp NOTIFY changed)
    Q_PROPERTY(qreal dwdpa READ dwdpa NOTIFY changed)
    Q_PROPERTY(qreal dwdpi READ dwdpi NOTIFY changed)
    Q_PROPERTY(qreal sem READ sem NOTIFY changed)
    Q_PROPERTY(qreal asem READ asem NOTIFY changed)
    Q_PROPERTY(qreal sspa READ sspa NOTIFY changed)
    Q_PROPERTY(qreal asspa READ asspa NOTIFY changed)
    Q_PROPERTY(qreal hem READ hem NOTIFY changed)
    Q_PROPERTY(qreal ahem READ ahem NOTIFY changed)
    Q_PROPERTY(qreal hspa READ hspa NOTIFY changed)
    Q_PROPERTY(qreal ahspa READ ahspa NOTIFY changed)
    Q_PROPERTY(qreal wem READ wem NOTIFY changed)
    Q_PROPERTY(qreal awem READ awem NOTIFY changed)
    Q_PROPERTY(qreal wspa READ wspa NOTIFY changed)
    Q_PROPERTY(qreal awspa READ awspa NOTIFY changed)
    Q_PROPERTY(qreal sdpPh READ sdpPh NOTIFY changed)
    Q_PROPERTY(qreal asdpPh READ asdpPh NOTIFY changed)
    Q_PROPERTY(qreal sdpLh READ sdpLh NOTIFY changed)
    Q_PROPERTY(qreal asdpLh READ asdpLh NOTIFY changed)
    Q_PROPERTY(qreal sdpPw READ sdpPw NOTIFY changed)
    Q_PROPERTY(qreal asdpPw READ asdpPw NOTIFY changed)
    Q_PROPERTY(qreal sdpLw READ sdpLw NOTIFY changed)
    Q_PROPERTY(qreal asdpLw READ asdpLw NOTIFY changed)
    Q_PROPERTY(qreal hdpLw READ hdpLw NOTIFY changed)
    Q_PROPERTY(qreal ahdpLw READ ahdpLw NOTIFY changed)
    Q_PROPERTY(qreal hdpPw READ hdpPw NOTIFY changed)
    Q_PROPERTY(qreal ahdpPw READ ahdpPw NOTIFY changed)
    Q_PROPERTY(qreal wdpLh READ wdpLh NOTIFY changed)
    Q_PROPERTY(qreal awdpLh READ awdpLh NOTIFY changed)
    Q_PROPERTY(qreal wdpPh READ wdpPh NOTIFY changed)
    Q_PROPERTY(qreal awdpPh READ awdpPh NOTIFY changed)
public:  // factor getters: size = value × factor
    qreal sdp() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S, 0)]; }
    qreal ssp() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal sdpa() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S, 1)]; }
    qreal sdpi() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S, 2)]; }
    qreal hdp() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_H, 0)]; }
    qreal hsp() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal hdpa() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_H, 1)]; }
    qreal hdpi() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_H, 2)]; }
    qreal wdp() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_W, 0)]; }
    qreal wsp() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal wdpa() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_W, 1)]; }
    qreal wdpi() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_W, 2)]; }
    qreal asdp() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S, 0)]; }
    qreal assp() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal asdpa() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S, 1)]; }
    qreal asdpi() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S, 2)]; }
    qreal ahdp() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_H, 0)]; }
    qreal ahsp() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal ahdpa() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_H, 1)]; }
    qreal ahdpi() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_H, 2)]; }
    qreal awdp() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_W, 0)]; }
    qreal awsp() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal awdpa() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_W, 1)]; }
    qreal awdpi() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_W, 2)]; }
    qreal psdp() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_S, 0)]; }
    qreal pssp() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal psdpa() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_S, 1)]; }
    qreal psdpi() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_S, 2)]; }
    qreal phdp() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_H, 0)]; }
    qreal phsp() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal phdpa() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_H, 1)]; }
    qreal phdpi() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_H, 2)]; }
    qreal pwdp() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_W, 0)]; }
    qreal pwsp() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal pwdpa() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_W, 1)]; }
    qreal pwdpi() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_W, 2)]; }
    qreal pwsdp() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_S, 0)]; }
    qreal pwssp() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal pwsdpa() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_S, 1)]; }
    qreal pwsdpi() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_S, 2)]; }
    qreal pwhdp() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_H, 0)]; }
    qreal pwhsp() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal pwhdpa() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_H, 1)]; }
    qreal pwhdpi() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_H, 2)]; }
    qreal pwwdp() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_W, 0)]; }
    qreal pwwsp() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal pwwdpa() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_W, 1)]; }
    qreal pwwdpi() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_W, 2)]; }
    qreal fsdp() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_S, 0)]; }
    qreal fssp() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal fsdpa() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_S, 1)]; }
    qreal fsdpi() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_S, 2)]; }
    qreal fhdp() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_H, 0)]; }
    qreal fhsp() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal fhdpa() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_H, 1)]; }
    qreal fhdpi() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_H, 2)]; }
    qreal fwdp() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_W, 0)]; }
    qreal fwsp() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal fwdpa() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_W, 1)]; }
    qreal fwdpi() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_W, 2)]; }
    qreal isdp() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_S, 0)]; }
    qreal issp() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal isdpa() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_S, 1)]; }
    qreal isdpi() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_S, 2)]; }
    qreal ihdp() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_H, 0)]; }
    qreal ihsp() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal ihdpa() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_H, 1)]; }
    qreal ihdpi() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_H, 2)]; }
    qreal iwdp() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_W, 0)]; }
    qreal iwsp() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal iwdpa() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_W, 1)]; }
    qreal iwdpi() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_W, 2)]; }
    qreal logsdp() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_S, 0)]; }
    qreal logssp() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal logsdpa() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_S, 1)]; }
    qreal logsdpi() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_S, 2)]; }
    qreal loghdp() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_H, 0)]; }
    qreal loghsp() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal loghdpa() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_H, 1)]; }
    qreal loghdpi() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_H, 2)]; }
    qreal logwdp() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_W, 0)]; }
    qreal logwsp() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal logwdpa() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_W, 1)]; }
    qreal logwdpi() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_W, 2)]; }
    qreal dgsdp() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_S, 0)]; }
    qreal dgssp() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal dgsdpa() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_S, 1)]; }
    qreal dgsdpi() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_S, 2)]; }
    qreal dghdp() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_H, 0)]; }
    qreal dghsp() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal dghdpa() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_H, 1)]; }
    qreal dghdpi() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_H, 2)]; }
    qreal dgwdp() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_W, 0)]; }
    qreal dgwsp() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal dgwdpa() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_W, 1)]; }
    qreal dgwdpi() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_W, 2)]; }
    qreal prsdp() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_S, 0)]; }
    qreal prssp() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal prsdpa() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_S, 1)]; }
    qreal prsdpi() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_S, 2)]; }
    qreal prhdp() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_H, 0)]; }
    qreal prhsp() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal prhdpa() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_H, 1)]; }
    qreal prhdpi() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_H, 2)]; }
    qreal prwdp() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_W, 0)]; }
    qreal prwsp() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal prwdpa() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_W, 1)]; }
    qreal prwdpi() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_W, 2)]; }
    qreal ftsdp() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_S, 0)]; }
    qreal ftssp() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal ftsdpa() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_S, 1)]; }
    qreal ftsdpi() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_S, 2)]; }
    qreal fthdp() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_H, 0)]; }
    qreal fthsp() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal fthdpa() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_H, 1)]; }
    qreal fthdpi() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_H, 2)]; }
    qreal ftwdp() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_W, 0)]; }
    qreal ftwsp() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal ftwdpa() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_W, 1)]; }
    qreal ftwdpi() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_W, 2)]; }
    qreal flsdp() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_S, 0)]; }
    qreal flssp() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal flsdpa() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_S, 1)]; }
    qreal flsdpi() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_S, 2)]; }
    qreal flhdp() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_H, 0)]; }
    qreal flhsp() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal flhdpa() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_H, 1)]; }
    qreal flhdpi() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_H, 2)]; }
    qreal flwdp() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_W, 0)]; }
    qreal flwsp() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal flwdpa() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_W, 1)]; }
    qreal flwdpi() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_W, 2)]; }
    qreal dsdp() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_S, 0)]; }
    qreal dssp() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal dsdpa() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_S, 1)]; }
    qreal dsdpi() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_S, 2)]; }
    qreal dhdp() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_H, 0)]; }
    qreal dhsp() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal dhdpa() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_H, 1)]; }
    qreal dhdpi() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_H, 2)]; }
    qreal dwdp() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_W, 0)]; }
    qreal dwsp() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal dwdpa() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_W, 1)]; }
    qreal dwdpi() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_W, 2)]; }
    qreal sem() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S, 0)]; }
    qreal asem() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S, 0)]; }
    qreal sspa() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S, 1)] * m_m.in.font_scale; }
    qreal asspa() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S, 1)] * m_m.in.font_scale; }
    qreal hem() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_H, 0)]; }
    qreal ahem() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_H, 0)]; }
    qreal hspa() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_H, 1)] * m_m.in.font_scale; }
    qreal ahspa() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_H, 1)] * m_m.in.font_scale; }
    qreal wem() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_W, 0)]; }
    qreal awem() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_W, 0)]; }
    qreal wspa() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_W, 1)] * m_m.in.font_scale; }
    qreal awspa() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_W, 1)] * m_m.in.font_scale; }
    qreal sdpPh() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S_PH, 0)]; }
    qreal asdpPh() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S_PH, 0)]; }
    qreal sdpLh() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S_LH, 0)]; }
    qreal asdpLh() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S_LH, 0)]; }
    qreal sdpPw() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S_PW, 0)]; }
    qreal asdpPw() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S_PW, 0)]; }
    qreal sdpLw() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S_LW, 0)]; }
    qreal asdpLw() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S_LW, 0)]; }
    qreal hdpLw() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_H_LW, 0)]; }
    qreal ahdpLw() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_H_LW, 0)]; }
    qreal hdpPw() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_H_PW, 0)]; }
    qreal ahdpPw() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_H_PW, 0)]; }
    qreal wdpLh() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_W_LH, 0)]; }
    qreal awdpLh() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_W_LH, 0)]; }
    qreal wdpPh() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_W_PH, 0)]; }
    qreal awdpPh() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_W_PH, 0)]; }
    // </generated>

public:
    explicit Scope(QObject *parent = nullptr);
    /// Tracks `window` (QWindow, QQuickWindow) or a QWidget (its top-level window is used).
    explicit Scope(QWindow *window, QObject *parent = nullptr);
    explicit Scope(QWidget *widget, QObject *parent = nullptr);
    ~Scope() override;

    /// The process-wide scope used by the QML singleton and the C++ literals. It follows
    /// the first window shown unless setTarget() is called.
    static Scope *global();

    /// Registers the QML module "AppDimens 1.0": singleton `AppDimens` and type `DimensScope`.
    static void registerQmlTypes(const char *uri = "AppDimens");

    // Tracking
    QObject *target() const;
    void setTarget(QObject *windowOrWidget);
    /// Publishes a snapshot manually (tests, offscreen rendering, custom platforms).
    void setInput(const ad_input &in);
    /// Re-reads the target now. Returns true when the snapshot changed.
    Q_INVOKABLE bool refresh();

    // Snapshot
    const ad_metrics &metrics() const { return m_m; }
    qreal width() const { return m_m.in.width; }
    qreal height() const { return m_m.in.height; }
    qreal smallestWidth() const { return m_m.sw; }
    qreal density() const { return m_m.in.density; }
    qreal fontScale() const { return m_m.in.font_scale; }
    qreal dpi() const { return m_m.in.dpi; }
    bool landscape() const { return m_m.is_landscape != 0; }
    bool portrait() const { return m_m.is_portrait != 0; }
    bool multiWindow() const { return m_m.in.multi_window != 0; }
    int uiMode() const { return int(m_m.in.ui_mode); }
    quint32 revision() const { return m_m.generation; }

    /// ≤ 0 restores automatic (1.0, or QT_SCALE_FACTOR-independent app font ratio if enabled).
    void setFontScale(qreal s);
    void setMultiWindow(bool on);
    void setUiMode(int mode);

    // Values (logical px). In QML bindings prefer the factor properties: `16 * AppDimens.sdp`.
    Q_INVOKABLE qreal dimen(const QString &expr, qreal fallback = 0) const;
    Q_INVOKABLE int px(const QString &expr) const;
    Q_INVOKABLE qreal resolve(const QString &token, qreal value) const;
    Q_INVOKABLE qreal factor(const QString &token) const;
    Q_INVOKABLE qreal spaceW(qreal percent) const { return ad_space_w(&m_m, percent); }
    Q_INVOKABLE qreal spaceH(qreal percent) const { return ad_space_h(&m_m, percent); }
    Q_INVOKABLE qreal mm(qreal v) const { return ad_mm(&m_m, v); }
    Q_INVOKABLE qreal inch(qreal v) const { return ad_inch(&m_m, v); }
    Q_INVOKABLE QString styleSheet(const QString &templ) const { return expandStyleSheet(m_m, templ); }

    /// Applies `templ` (with tokens) to `w` now and on every change.
    void bindStyleSheet(QWidget *w, const QString &templ);
    void unbindStyleSheet(QWidget *w);

signals:
    void changed();
    void targetChanged();

protected:
    bool eventFilter(QObject *o, QEvent *e) override;

private:
    void attachWindow(QWindow *w);
    void hookScreen(QScreen *s);
    bool publish(const ad_input &in);
    void applyStyleSheets();
    ad_input read() const;

    ad_metrics m_m;
    QPointer<QObject> m_target;
    QPointer<QWindow> m_window;
    QPointer<QScreen> m_screen;
    QVector<QMetaObject::Connection> m_conns;
    QVector<QMetaObject::Connection> m_screenConns;
    QHash<QWidget *, QString> m_sheets;
    qreal m_fontOverride = 0;
    bool m_mwOverride = false;
    bool m_mwSet = false;
    ad_ui_mode m_ui = AD_UI_NORMAL;
    bool m_manual = false;
    mutable QHash<QString, ad_token> m_tokenCache;
};

namespace literals {
// Global-scope literals (logical px): 16_sdp, 14_ssp, 12.5_asdp …
inline qreal operator""_sdp(long double v) { return ad_sdp(&Scope::global()->metrics(), ad_real(v)); }
inline qreal operator""_sdp(unsigned long long v) { return ad_sdp(&Scope::global()->metrics(), ad_real(v)); }
inline qreal operator""_hdp(unsigned long long v) { return ad_hdp(&Scope::global()->metrics(), ad_real(v)); }
inline qreal operator""_wdp(unsigned long long v) { return ad_wdp(&Scope::global()->metrics(), ad_real(v)); }
inline qreal operator""_ssp(unsigned long long v) { return ad_ssp(&Scope::global()->metrics(), ad_real(v)); }
inline qreal operator""_ssp(long double v) { return ad_ssp(&Scope::global()->metrics(), ad_real(v)); }
inline qreal operator""_sem(unsigned long long v) { return ad_sem(&Scope::global()->metrics(), ad_real(v)); }
inline qreal operator""_asdp(unsigned long long v) { return ad_asdp(&Scope::global()->metrics(), ad_real(v)); }
inline qreal operator""_asdp(long double v) { return ad_asdp(&Scope::global()->metrics(), ad_real(v)); }
inline qreal operator""_assp(unsigned long long v) { return ad_assp(&Scope::global()->metrics(), ad_real(v)); }
inline qreal operator""_ftsdp(unsigned long long v) { return ad_ftsdp(&Scope::global()->metrics(), ad_real(v)); }
inline qreal operator""_flsdp(unsigned long long v) { return ad_flsdp(&Scope::global()->metrics(), ad_real(v)); }
} // namespace literals

} // namespace AppDimens
