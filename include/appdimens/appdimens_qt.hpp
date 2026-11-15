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
    Q_PROPERTY(qreal sdp READ sdpFactor NOTIFY changed)
    Q_PROPERTY(qreal ssp READ sspFactor NOTIFY changed)
    Q_PROPERTY(qreal sdpa READ sdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal sdpi READ sdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal hdp READ hdpFactor NOTIFY changed)
    Q_PROPERTY(qreal hsp READ hspFactor NOTIFY changed)
    Q_PROPERTY(qreal hdpa READ hdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal hdpi READ hdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal wdp READ wdpFactor NOTIFY changed)
    Q_PROPERTY(qreal wsp READ wspFactor NOTIFY changed)
    Q_PROPERTY(qreal wdpa READ wdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal wdpi READ wdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal asdp READ asdpFactor NOTIFY changed)
    Q_PROPERTY(qreal assp READ asspFactor NOTIFY changed)
    Q_PROPERTY(qreal asdpa READ asdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal asdpi READ asdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal ahdp READ ahdpFactor NOTIFY changed)
    Q_PROPERTY(qreal ahsp READ ahspFactor NOTIFY changed)
    Q_PROPERTY(qreal ahdpa READ ahdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal ahdpi READ ahdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal awdp READ awdpFactor NOTIFY changed)
    Q_PROPERTY(qreal awsp READ awspFactor NOTIFY changed)
    Q_PROPERTY(qreal awdpa READ awdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal awdpi READ awdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal psdp READ psdpFactor NOTIFY changed)
    Q_PROPERTY(qreal pssp READ psspFactor NOTIFY changed)
    Q_PROPERTY(qreal psdpa READ psdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal psdpi READ psdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal phdp READ phdpFactor NOTIFY changed)
    Q_PROPERTY(qreal phsp READ phspFactor NOTIFY changed)
    Q_PROPERTY(qreal phdpa READ phdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal phdpi READ phdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal pwdp READ pwdpFactor NOTIFY changed)
    Q_PROPERTY(qreal pwsp READ pwspFactor NOTIFY changed)
    Q_PROPERTY(qreal pwdpa READ pwdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal pwdpi READ pwdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal pwsdp READ pwsdpFactor NOTIFY changed)
    Q_PROPERTY(qreal pwssp READ pwsspFactor NOTIFY changed)
    Q_PROPERTY(qreal pwsdpa READ pwsdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal pwsdpi READ pwsdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal pwhdp READ pwhdpFactor NOTIFY changed)
    Q_PROPERTY(qreal pwhsp READ pwhspFactor NOTIFY changed)
    Q_PROPERTY(qreal pwhdpa READ pwhdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal pwhdpi READ pwhdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal pwwdp READ pwwdpFactor NOTIFY changed)
    Q_PROPERTY(qreal pwwsp READ pwwspFactor NOTIFY changed)
    Q_PROPERTY(qreal pwwdpa READ pwwdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal pwwdpi READ pwwdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal fsdp READ fsdpFactor NOTIFY changed)
    Q_PROPERTY(qreal fssp READ fsspFactor NOTIFY changed)
    Q_PROPERTY(qreal fsdpa READ fsdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal fsdpi READ fsdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal fhdp READ fhdpFactor NOTIFY changed)
    Q_PROPERTY(qreal fhsp READ fhspFactor NOTIFY changed)
    Q_PROPERTY(qreal fhdpa READ fhdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal fhdpi READ fhdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal fwdp READ fwdpFactor NOTIFY changed)
    Q_PROPERTY(qreal fwsp READ fwspFactor NOTIFY changed)
    Q_PROPERTY(qreal fwdpa READ fwdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal fwdpi READ fwdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal isdp READ isdpFactor NOTIFY changed)
    Q_PROPERTY(qreal issp READ isspFactor NOTIFY changed)
    Q_PROPERTY(qreal isdpa READ isdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal isdpi READ isdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal ihdp READ ihdpFactor NOTIFY changed)
    Q_PROPERTY(qreal ihsp READ ihspFactor NOTIFY changed)
    Q_PROPERTY(qreal ihdpa READ ihdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal ihdpi READ ihdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal iwdp READ iwdpFactor NOTIFY changed)
    Q_PROPERTY(qreal iwsp READ iwspFactor NOTIFY changed)
    Q_PROPERTY(qreal iwdpa READ iwdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal iwdpi READ iwdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal logsdp READ logsdpFactor NOTIFY changed)
    Q_PROPERTY(qreal logssp READ logsspFactor NOTIFY changed)
    Q_PROPERTY(qreal logsdpa READ logsdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal logsdpi READ logsdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal loghdp READ loghdpFactor NOTIFY changed)
    Q_PROPERTY(qreal loghsp READ loghspFactor NOTIFY changed)
    Q_PROPERTY(qreal loghdpa READ loghdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal loghdpi READ loghdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal logwdp READ logwdpFactor NOTIFY changed)
    Q_PROPERTY(qreal logwsp READ logwspFactor NOTIFY changed)
    Q_PROPERTY(qreal logwdpa READ logwdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal logwdpi READ logwdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal dgsdp READ dgsdpFactor NOTIFY changed)
    Q_PROPERTY(qreal dgssp READ dgsspFactor NOTIFY changed)
    Q_PROPERTY(qreal dgsdpa READ dgsdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal dgsdpi READ dgsdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal dghdp READ dghdpFactor NOTIFY changed)
    Q_PROPERTY(qreal dghsp READ dghspFactor NOTIFY changed)
    Q_PROPERTY(qreal dghdpa READ dghdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal dghdpi READ dghdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal dgwdp READ dgwdpFactor NOTIFY changed)
    Q_PROPERTY(qreal dgwsp READ dgwspFactor NOTIFY changed)
    Q_PROPERTY(qreal dgwdpa READ dgwdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal dgwdpi READ dgwdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal prsdp READ prsdpFactor NOTIFY changed)
    Q_PROPERTY(qreal prssp READ prsspFactor NOTIFY changed)
    Q_PROPERTY(qreal prsdpa READ prsdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal prsdpi READ prsdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal prhdp READ prhdpFactor NOTIFY changed)
    Q_PROPERTY(qreal prhsp READ prhspFactor NOTIFY changed)
    Q_PROPERTY(qreal prhdpa READ prhdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal prhdpi READ prhdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal prwdp READ prwdpFactor NOTIFY changed)
    Q_PROPERTY(qreal prwsp READ prwspFactor NOTIFY changed)
    Q_PROPERTY(qreal prwdpa READ prwdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal prwdpi READ prwdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal ftsdp READ ftsdpFactor NOTIFY changed)
    Q_PROPERTY(qreal ftssp READ ftsspFactor NOTIFY changed)
    Q_PROPERTY(qreal ftsdpa READ ftsdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal ftsdpi READ ftsdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal fthdp READ fthdpFactor NOTIFY changed)
    Q_PROPERTY(qreal fthsp READ fthspFactor NOTIFY changed)
    Q_PROPERTY(qreal fthdpa READ fthdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal fthdpi READ fthdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal ftwdp READ ftwdpFactor NOTIFY changed)
    Q_PROPERTY(qreal ftwsp READ ftwspFactor NOTIFY changed)
    Q_PROPERTY(qreal ftwdpa READ ftwdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal ftwdpi READ ftwdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal flsdp READ flsdpFactor NOTIFY changed)
    Q_PROPERTY(qreal flssp READ flsspFactor NOTIFY changed)
    Q_PROPERTY(qreal flsdpa READ flsdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal flsdpi READ flsdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal flhdp READ flhdpFactor NOTIFY changed)
    Q_PROPERTY(qreal flhsp READ flhspFactor NOTIFY changed)
    Q_PROPERTY(qreal flhdpa READ flhdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal flhdpi READ flhdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal flwdp READ flwdpFactor NOTIFY changed)
    Q_PROPERTY(qreal flwsp READ flwspFactor NOTIFY changed)
    Q_PROPERTY(qreal flwdpa READ flwdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal flwdpi READ flwdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal dsdp READ dsdpFactor NOTIFY changed)
    Q_PROPERTY(qreal dssp READ dsspFactor NOTIFY changed)
    Q_PROPERTY(qreal dsdpa READ dsdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal dsdpi READ dsdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal dhdp READ dhdpFactor NOTIFY changed)
    Q_PROPERTY(qreal dhsp READ dhspFactor NOTIFY changed)
    Q_PROPERTY(qreal dhdpa READ dhdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal dhdpi READ dhdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal dwdp READ dwdpFactor NOTIFY changed)
    Q_PROPERTY(qreal dwsp READ dwspFactor NOTIFY changed)
    Q_PROPERTY(qreal dwdpa READ dwdpaFactor NOTIFY changed)
    Q_PROPERTY(qreal dwdpi READ dwdpiFactor NOTIFY changed)
    Q_PROPERTY(qreal sem READ semFactor NOTIFY changed)
    Q_PROPERTY(qreal asem READ asemFactor NOTIFY changed)
    Q_PROPERTY(qreal sspa READ sspaFactor NOTIFY changed)
    Q_PROPERTY(qreal asspa READ asspaFactor NOTIFY changed)
    Q_PROPERTY(qreal hem READ hemFactor NOTIFY changed)
    Q_PROPERTY(qreal ahem READ ahemFactor NOTIFY changed)
    Q_PROPERTY(qreal hspa READ hspaFactor NOTIFY changed)
    Q_PROPERTY(qreal ahspa READ ahspaFactor NOTIFY changed)
    Q_PROPERTY(qreal wem READ wemFactor NOTIFY changed)
    Q_PROPERTY(qreal awem READ awemFactor NOTIFY changed)
    Q_PROPERTY(qreal wspa READ wspaFactor NOTIFY changed)
    Q_PROPERTY(qreal awspa READ awspaFactor NOTIFY changed)
    Q_PROPERTY(qreal sdpPh READ sdpPhFactor NOTIFY changed)
    Q_PROPERTY(qreal asdpPh READ asdpPhFactor NOTIFY changed)
    Q_PROPERTY(qreal sdpLh READ sdpLhFactor NOTIFY changed)
    Q_PROPERTY(qreal asdpLh READ asdpLhFactor NOTIFY changed)
    Q_PROPERTY(qreal sdpPw READ sdpPwFactor NOTIFY changed)
    Q_PROPERTY(qreal asdpPw READ asdpPwFactor NOTIFY changed)
    Q_PROPERTY(qreal sdpLw READ sdpLwFactor NOTIFY changed)
    Q_PROPERTY(qreal asdpLw READ asdpLwFactor NOTIFY changed)
    Q_PROPERTY(qreal hdpLw READ hdpLwFactor NOTIFY changed)
    Q_PROPERTY(qreal ahdpLw READ ahdpLwFactor NOTIFY changed)
    Q_PROPERTY(qreal hdpPw READ hdpPwFactor NOTIFY changed)
    Q_PROPERTY(qreal ahdpPw READ ahdpPwFactor NOTIFY changed)
    Q_PROPERTY(qreal wdpLh READ wdpLhFactor NOTIFY changed)
    Q_PROPERTY(qreal awdpLh READ awdpLhFactor NOTIFY changed)
    Q_PROPERTY(qreal wdpPh READ wdpPhFactor NOTIFY changed)
    Q_PROPERTY(qreal awdpPh READ awdpPhFactor NOTIFY changed)
public:  // tokens: ad->sdp(16) = 16 × factor (logical px) · factors: ad->sdpFactor()
    qreal sdpFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S, 0)]; }
    qreal sdp(qreal v) const { return v * sdpFactor(); }
    qreal sspFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal ssp(qreal v) const { return v * sspFactor(); }
    qreal sdpaFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S, 1)]; }
    qreal sdpa(qreal v) const { return v * sdpaFactor(); }
    qreal sdpiFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S, 2)]; }
    qreal sdpi(qreal v) const { return v * sdpiFactor(); }
    qreal hdpFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_H, 0)]; }
    qreal hdp(qreal v) const { return v * hdpFactor(); }
    qreal hspFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal hsp(qreal v) const { return v * hspFactor(); }
    qreal hdpaFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_H, 1)]; }
    qreal hdpa(qreal v) const { return v * hdpaFactor(); }
    qreal hdpiFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_H, 2)]; }
    qreal hdpi(qreal v) const { return v * hdpiFactor(); }
    qreal wdpFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_W, 0)]; }
    qreal wdp(qreal v) const { return v * wdpFactor(); }
    qreal wspFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal wsp(qreal v) const { return v * wspFactor(); }
    qreal wdpaFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_W, 1)]; }
    qreal wdpa(qreal v) const { return v * wdpaFactor(); }
    qreal wdpiFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_W, 2)]; }
    qreal wdpi(qreal v) const { return v * wdpiFactor(); }
    qreal asdpFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S, 0)]; }
    qreal asdp(qreal v) const { return v * asdpFactor(); }
    qreal asspFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal assp(qreal v) const { return v * asspFactor(); }
    qreal asdpaFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S, 1)]; }
    qreal asdpa(qreal v) const { return v * asdpaFactor(); }
    qreal asdpiFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S, 2)]; }
    qreal asdpi(qreal v) const { return v * asdpiFactor(); }
    qreal ahdpFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_H, 0)]; }
    qreal ahdp(qreal v) const { return v * ahdpFactor(); }
    qreal ahspFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal ahsp(qreal v) const { return v * ahspFactor(); }
    qreal ahdpaFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_H, 1)]; }
    qreal ahdpa(qreal v) const { return v * ahdpaFactor(); }
    qreal ahdpiFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_H, 2)]; }
    qreal ahdpi(qreal v) const { return v * ahdpiFactor(); }
    qreal awdpFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_W, 0)]; }
    qreal awdp(qreal v) const { return v * awdpFactor(); }
    qreal awspFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal awsp(qreal v) const { return v * awspFactor(); }
    qreal awdpaFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_W, 1)]; }
    qreal awdpa(qreal v) const { return v * awdpaFactor(); }
    qreal awdpiFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_W, 2)]; }
    qreal awdpi(qreal v) const { return v * awdpiFactor(); }
    qreal psdpFactor() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_S, 0)]; }
    qreal psdp(qreal v) const { return v * psdpFactor(); }
    qreal psspFactor() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal pssp(qreal v) const { return v * psspFactor(); }
    qreal psdpaFactor() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_S, 1)]; }
    qreal psdpa(qreal v) const { return v * psdpaFactor(); }
    qreal psdpiFactor() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_S, 2)]; }
    qreal psdpi(qreal v) const { return v * psdpiFactor(); }
    qreal phdpFactor() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_H, 0)]; }
    qreal phdp(qreal v) const { return v * phdpFactor(); }
    qreal phspFactor() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal phsp(qreal v) const { return v * phspFactor(); }
    qreal phdpaFactor() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_H, 1)]; }
    qreal phdpa(qreal v) const { return v * phdpaFactor(); }
    qreal phdpiFactor() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_H, 2)]; }
    qreal phdpi(qreal v) const { return v * phdpiFactor(); }
    qreal pwdpFactor() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_W, 0)]; }
    qreal pwdp(qreal v) const { return v * pwdpFactor(); }
    qreal pwspFactor() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal pwsp(qreal v) const { return v * pwspFactor(); }
    qreal pwdpaFactor() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_W, 1)]; }
    qreal pwdpa(qreal v) const { return v * pwdpaFactor(); }
    qreal pwdpiFactor() const { return m_m.table[AD_PERCENT][AD_SLOT(AD_VAR_W, 2)]; }
    qreal pwdpi(qreal v) const { return v * pwdpiFactor(); }
    qreal pwsdpFactor() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_S, 0)]; }
    qreal pwsdp(qreal v) const { return v * pwsdpFactor(); }
    qreal pwsspFactor() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal pwssp(qreal v) const { return v * pwsspFactor(); }
    qreal pwsdpaFactor() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_S, 1)]; }
    qreal pwsdpa(qreal v) const { return v * pwsdpaFactor(); }
    qreal pwsdpiFactor() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_S, 2)]; }
    qreal pwsdpi(qreal v) const { return v * pwsdpiFactor(); }
    qreal pwhdpFactor() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_H, 0)]; }
    qreal pwhdp(qreal v) const { return v * pwhdpFactor(); }
    qreal pwhspFactor() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal pwhsp(qreal v) const { return v * pwhspFactor(); }
    qreal pwhdpaFactor() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_H, 1)]; }
    qreal pwhdpa(qreal v) const { return v * pwhdpaFactor(); }
    qreal pwhdpiFactor() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_H, 2)]; }
    qreal pwhdpi(qreal v) const { return v * pwhdpiFactor(); }
    qreal pwwdpFactor() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_W, 0)]; }
    qreal pwwdp(qreal v) const { return v * pwwdpFactor(); }
    qreal pwwspFactor() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal pwwsp(qreal v) const { return v * pwwspFactor(); }
    qreal pwwdpaFactor() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_W, 1)]; }
    qreal pwwdpa(qreal v) const { return v * pwwdpaFactor(); }
    qreal pwwdpiFactor() const { return m_m.table[AD_POWER][AD_SLOT(AD_VAR_W, 2)]; }
    qreal pwwdpi(qreal v) const { return v * pwwdpiFactor(); }
    qreal fsdpFactor() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_S, 0)]; }
    qreal fsdp(qreal v) const { return v * fsdpFactor(); }
    qreal fsspFactor() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal fssp(qreal v) const { return v * fsspFactor(); }
    qreal fsdpaFactor() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_S, 1)]; }
    qreal fsdpa(qreal v) const { return v * fsdpaFactor(); }
    qreal fsdpiFactor() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_S, 2)]; }
    qreal fsdpi(qreal v) const { return v * fsdpiFactor(); }
    qreal fhdpFactor() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_H, 0)]; }
    qreal fhdp(qreal v) const { return v * fhdpFactor(); }
    qreal fhspFactor() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal fhsp(qreal v) const { return v * fhspFactor(); }
    qreal fhdpaFactor() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_H, 1)]; }
    qreal fhdpa(qreal v) const { return v * fhdpaFactor(); }
    qreal fhdpiFactor() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_H, 2)]; }
    qreal fhdpi(qreal v) const { return v * fhdpiFactor(); }
    qreal fwdpFactor() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_W, 0)]; }
    qreal fwdp(qreal v) const { return v * fwdpFactor(); }
    qreal fwspFactor() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal fwsp(qreal v) const { return v * fwspFactor(); }
    qreal fwdpaFactor() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_W, 1)]; }
    qreal fwdpa(qreal v) const { return v * fwdpaFactor(); }
    qreal fwdpiFactor() const { return m_m.table[AD_FLUID][AD_SLOT(AD_VAR_W, 2)]; }
    qreal fwdpi(qreal v) const { return v * fwdpiFactor(); }
    qreal isdpFactor() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_S, 0)]; }
    qreal isdp(qreal v) const { return v * isdpFactor(); }
    qreal isspFactor() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal issp(qreal v) const { return v * isspFactor(); }
    qreal isdpaFactor() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_S, 1)]; }
    qreal isdpa(qreal v) const { return v * isdpaFactor(); }
    qreal isdpiFactor() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_S, 2)]; }
    qreal isdpi(qreal v) const { return v * isdpiFactor(); }
    qreal ihdpFactor() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_H, 0)]; }
    qreal ihdp(qreal v) const { return v * ihdpFactor(); }
    qreal ihspFactor() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal ihsp(qreal v) const { return v * ihspFactor(); }
    qreal ihdpaFactor() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_H, 1)]; }
    qreal ihdpa(qreal v) const { return v * ihdpaFactor(); }
    qreal ihdpiFactor() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_H, 2)]; }
    qreal ihdpi(qreal v) const { return v * ihdpiFactor(); }
    qreal iwdpFactor() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_W, 0)]; }
    qreal iwdp(qreal v) const { return v * iwdpFactor(); }
    qreal iwspFactor() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal iwsp(qreal v) const { return v * iwspFactor(); }
    qreal iwdpaFactor() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_W, 1)]; }
    qreal iwdpa(qreal v) const { return v * iwdpaFactor(); }
    qreal iwdpiFactor() const { return m_m.table[AD_INTERPOLATED][AD_SLOT(AD_VAR_W, 2)]; }
    qreal iwdpi(qreal v) const { return v * iwdpiFactor(); }
    qreal logsdpFactor() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_S, 0)]; }
    qreal logsdp(qreal v) const { return v * logsdpFactor(); }
    qreal logsspFactor() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal logssp(qreal v) const { return v * logsspFactor(); }
    qreal logsdpaFactor() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_S, 1)]; }
    qreal logsdpa(qreal v) const { return v * logsdpaFactor(); }
    qreal logsdpiFactor() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_S, 2)]; }
    qreal logsdpi(qreal v) const { return v * logsdpiFactor(); }
    qreal loghdpFactor() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_H, 0)]; }
    qreal loghdp(qreal v) const { return v * loghdpFactor(); }
    qreal loghspFactor() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal loghsp(qreal v) const { return v * loghspFactor(); }
    qreal loghdpaFactor() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_H, 1)]; }
    qreal loghdpa(qreal v) const { return v * loghdpaFactor(); }
    qreal loghdpiFactor() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_H, 2)]; }
    qreal loghdpi(qreal v) const { return v * loghdpiFactor(); }
    qreal logwdpFactor() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_W, 0)]; }
    qreal logwdp(qreal v) const { return v * logwdpFactor(); }
    qreal logwspFactor() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal logwsp(qreal v) const { return v * logwspFactor(); }
    qreal logwdpaFactor() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_W, 1)]; }
    qreal logwdpa(qreal v) const { return v * logwdpaFactor(); }
    qreal logwdpiFactor() const { return m_m.table[AD_LOGARITHMIC][AD_SLOT(AD_VAR_W, 2)]; }
    qreal logwdpi(qreal v) const { return v * logwdpiFactor(); }
    qreal dgsdpFactor() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_S, 0)]; }
    qreal dgsdp(qreal v) const { return v * dgsdpFactor(); }
    qreal dgsspFactor() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal dgssp(qreal v) const { return v * dgsspFactor(); }
    qreal dgsdpaFactor() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_S, 1)]; }
    qreal dgsdpa(qreal v) const { return v * dgsdpaFactor(); }
    qreal dgsdpiFactor() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_S, 2)]; }
    qreal dgsdpi(qreal v) const { return v * dgsdpiFactor(); }
    qreal dghdpFactor() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_H, 0)]; }
    qreal dghdp(qreal v) const { return v * dghdpFactor(); }
    qreal dghspFactor() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal dghsp(qreal v) const { return v * dghspFactor(); }
    qreal dghdpaFactor() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_H, 1)]; }
    qreal dghdpa(qreal v) const { return v * dghdpaFactor(); }
    qreal dghdpiFactor() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_H, 2)]; }
    qreal dghdpi(qreal v) const { return v * dghdpiFactor(); }
    qreal dgwdpFactor() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_W, 0)]; }
    qreal dgwdp(qreal v) const { return v * dgwdpFactor(); }
    qreal dgwspFactor() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal dgwsp(qreal v) const { return v * dgwspFactor(); }
    qreal dgwdpaFactor() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_W, 1)]; }
    qreal dgwdpa(qreal v) const { return v * dgwdpaFactor(); }
    qreal dgwdpiFactor() const { return m_m.table[AD_DIAGONAL][AD_SLOT(AD_VAR_W, 2)]; }
    qreal dgwdpi(qreal v) const { return v * dgwdpiFactor(); }
    qreal prsdpFactor() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_S, 0)]; }
    qreal prsdp(qreal v) const { return v * prsdpFactor(); }
    qreal prsspFactor() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal prssp(qreal v) const { return v * prsspFactor(); }
    qreal prsdpaFactor() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_S, 1)]; }
    qreal prsdpa(qreal v) const { return v * prsdpaFactor(); }
    qreal prsdpiFactor() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_S, 2)]; }
    qreal prsdpi(qreal v) const { return v * prsdpiFactor(); }
    qreal prhdpFactor() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_H, 0)]; }
    qreal prhdp(qreal v) const { return v * prhdpFactor(); }
    qreal prhspFactor() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal prhsp(qreal v) const { return v * prhspFactor(); }
    qreal prhdpaFactor() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_H, 1)]; }
    qreal prhdpa(qreal v) const { return v * prhdpaFactor(); }
    qreal prhdpiFactor() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_H, 2)]; }
    qreal prhdpi(qreal v) const { return v * prhdpiFactor(); }
    qreal prwdpFactor() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_W, 0)]; }
    qreal prwdp(qreal v) const { return v * prwdpFactor(); }
    qreal prwspFactor() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal prwsp(qreal v) const { return v * prwspFactor(); }
    qreal prwdpaFactor() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_W, 1)]; }
    qreal prwdpa(qreal v) const { return v * prwdpaFactor(); }
    qreal prwdpiFactor() const { return m_m.table[AD_PERIMETER][AD_SLOT(AD_VAR_W, 2)]; }
    qreal prwdpi(qreal v) const { return v * prwdpiFactor(); }
    qreal ftsdpFactor() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_S, 0)]; }
    qreal ftsdp(qreal v) const { return v * ftsdpFactor(); }
    qreal ftsspFactor() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal ftssp(qreal v) const { return v * ftsspFactor(); }
    qreal ftsdpaFactor() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_S, 1)]; }
    qreal ftsdpa(qreal v) const { return v * ftsdpaFactor(); }
    qreal ftsdpiFactor() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_S, 2)]; }
    qreal ftsdpi(qreal v) const { return v * ftsdpiFactor(); }
    qreal fthdpFactor() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_H, 0)]; }
    qreal fthdp(qreal v) const { return v * fthdpFactor(); }
    qreal fthspFactor() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal fthsp(qreal v) const { return v * fthspFactor(); }
    qreal fthdpaFactor() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_H, 1)]; }
    qreal fthdpa(qreal v) const { return v * fthdpaFactor(); }
    qreal fthdpiFactor() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_H, 2)]; }
    qreal fthdpi(qreal v) const { return v * fthdpiFactor(); }
    qreal ftwdpFactor() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_W, 0)]; }
    qreal ftwdp(qreal v) const { return v * ftwdpFactor(); }
    qreal ftwspFactor() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal ftwsp(qreal v) const { return v * ftwspFactor(); }
    qreal ftwdpaFactor() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_W, 1)]; }
    qreal ftwdpa(qreal v) const { return v * ftwdpaFactor(); }
    qreal ftwdpiFactor() const { return m_m.table[AD_FIT][AD_SLOT(AD_VAR_W, 2)]; }
    qreal ftwdpi(qreal v) const { return v * ftwdpiFactor(); }
    qreal flsdpFactor() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_S, 0)]; }
    qreal flsdp(qreal v) const { return v * flsdpFactor(); }
    qreal flsspFactor() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal flssp(qreal v) const { return v * flsspFactor(); }
    qreal flsdpaFactor() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_S, 1)]; }
    qreal flsdpa(qreal v) const { return v * flsdpaFactor(); }
    qreal flsdpiFactor() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_S, 2)]; }
    qreal flsdpi(qreal v) const { return v * flsdpiFactor(); }
    qreal flhdpFactor() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_H, 0)]; }
    qreal flhdp(qreal v) const { return v * flhdpFactor(); }
    qreal flhspFactor() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal flhsp(qreal v) const { return v * flhspFactor(); }
    qreal flhdpaFactor() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_H, 1)]; }
    qreal flhdpa(qreal v) const { return v * flhdpaFactor(); }
    qreal flhdpiFactor() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_H, 2)]; }
    qreal flhdpi(qreal v) const { return v * flhdpiFactor(); }
    qreal flwdpFactor() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_W, 0)]; }
    qreal flwdp(qreal v) const { return v * flwdpFactor(); }
    qreal flwspFactor() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal flwsp(qreal v) const { return v * flwspFactor(); }
    qreal flwdpaFactor() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_W, 1)]; }
    qreal flwdpa(qreal v) const { return v * flwdpaFactor(); }
    qreal flwdpiFactor() const { return m_m.table[AD_FILL][AD_SLOT(AD_VAR_W, 2)]; }
    qreal flwdpi(qreal v) const { return v * flwdpiFactor(); }
    qreal dsdpFactor() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_S, 0)]; }
    qreal dsdp(qreal v) const { return v * dsdpFactor(); }
    qreal dsspFactor() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_S, 0)] * m_m.in.font_scale; }
    qreal dssp(qreal v) const { return v * dsspFactor(); }
    qreal dsdpaFactor() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_S, 1)]; }
    qreal dsdpa(qreal v) const { return v * dsdpaFactor(); }
    qreal dsdpiFactor() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_S, 2)]; }
    qreal dsdpi(qreal v) const { return v * dsdpiFactor(); }
    qreal dhdpFactor() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_H, 0)]; }
    qreal dhdp(qreal v) const { return v * dhdpFactor(); }
    qreal dhspFactor() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_H, 0)] * m_m.in.font_scale; }
    qreal dhsp(qreal v) const { return v * dhspFactor(); }
    qreal dhdpaFactor() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_H, 1)]; }
    qreal dhdpa(qreal v) const { return v * dhdpaFactor(); }
    qreal dhdpiFactor() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_H, 2)]; }
    qreal dhdpi(qreal v) const { return v * dhdpiFactor(); }
    qreal dwdpFactor() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_W, 0)]; }
    qreal dwdp(qreal v) const { return v * dwdpFactor(); }
    qreal dwspFactor() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_W, 0)] * m_m.in.font_scale; }
    qreal dwsp(qreal v) const { return v * dwspFactor(); }
    qreal dwdpaFactor() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_W, 1)]; }
    qreal dwdpa(qreal v) const { return v * dwdpaFactor(); }
    qreal dwdpiFactor() const { return m_m.table[AD_DENSITY][AD_SLOT(AD_VAR_W, 2)]; }
    qreal dwdpi(qreal v) const { return v * dwdpiFactor(); }
    qreal semFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S, 0)]; }
    qreal sem(qreal v) const { return v * semFactor(); }
    qreal asemFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S, 0)]; }
    qreal asem(qreal v) const { return v * asemFactor(); }
    qreal sspaFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S, 1)] * m_m.in.font_scale; }
    qreal sspa(qreal v) const { return v * sspaFactor(); }
    qreal asspaFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S, 1)] * m_m.in.font_scale; }
    qreal asspa(qreal v) const { return v * asspaFactor(); }
    qreal hemFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_H, 0)]; }
    qreal hem(qreal v) const { return v * hemFactor(); }
    qreal ahemFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_H, 0)]; }
    qreal ahem(qreal v) const { return v * ahemFactor(); }
    qreal hspaFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_H, 1)] * m_m.in.font_scale; }
    qreal hspa(qreal v) const { return v * hspaFactor(); }
    qreal ahspaFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_H, 1)] * m_m.in.font_scale; }
    qreal ahspa(qreal v) const { return v * ahspaFactor(); }
    qreal wemFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_W, 0)]; }
    qreal wem(qreal v) const { return v * wemFactor(); }
    qreal awemFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_W, 0)]; }
    qreal awem(qreal v) const { return v * awemFactor(); }
    qreal wspaFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_W, 1)] * m_m.in.font_scale; }
    qreal wspa(qreal v) const { return v * wspaFactor(); }
    qreal awspaFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_W, 1)] * m_m.in.font_scale; }
    qreal awspa(qreal v) const { return v * awspaFactor(); }
    qreal sdpPhFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S_PH, 0)]; }
    qreal sdpPh(qreal v) const { return v * sdpPhFactor(); }
    qreal asdpPhFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S_PH, 0)]; }
    qreal asdpPh(qreal v) const { return v * asdpPhFactor(); }
    qreal sdpLhFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S_LH, 0)]; }
    qreal sdpLh(qreal v) const { return v * sdpLhFactor(); }
    qreal asdpLhFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S_LH, 0)]; }
    qreal asdpLh(qreal v) const { return v * asdpLhFactor(); }
    qreal sdpPwFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S_PW, 0)]; }
    qreal sdpPw(qreal v) const { return v * sdpPwFactor(); }
    qreal asdpPwFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S_PW, 0)]; }
    qreal asdpPw(qreal v) const { return v * asdpPwFactor(); }
    qreal sdpLwFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_S_LW, 0)]; }
    qreal sdpLw(qreal v) const { return v * sdpLwFactor(); }
    qreal asdpLwFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_S_LW, 0)]; }
    qreal asdpLw(qreal v) const { return v * asdpLwFactor(); }
    qreal hdpLwFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_H_LW, 0)]; }
    qreal hdpLw(qreal v) const { return v * hdpLwFactor(); }
    qreal ahdpLwFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_H_LW, 0)]; }
    qreal ahdpLw(qreal v) const { return v * ahdpLwFactor(); }
    qreal hdpPwFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_H_PW, 0)]; }
    qreal hdpPw(qreal v) const { return v * hdpPwFactor(); }
    qreal ahdpPwFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_H_PW, 0)]; }
    qreal ahdpPw(qreal v) const { return v * ahdpPwFactor(); }
    qreal wdpLhFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_W_LH, 0)]; }
    qreal wdpLh(qreal v) const { return v * wdpLhFactor(); }
    qreal awdpLhFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_W_LH, 0)]; }
    qreal awdpLh(qreal v) const { return v * awdpLhFactor(); }
    qreal wdpPhFactor() const { return m_m.table[AD_SCALED][AD_SLOT(AD_VAR_W_PH, 0)]; }
    qreal wdpPh(qreal v) const { return v * wdpPhFactor(); }
    qreal awdpPhFactor() const { return m_m.table[AD_AUTO][AD_SLOT(AD_VAR_W_PH, 0)]; }
    qreal awdpPh(qreal v) const { return v * awdpPhFactor(); }
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

    // <generated-free> by tools/gen_properties.py — do not edit by hand
// Global scope (Scope::global()), the AppDimens way: AppDimens::sdp(16), AppDimens::asdp(280) …
inline qreal sdp(qreal v) { return Scope::global()->sdp(v); }
inline qreal ssp(qreal v) { return Scope::global()->ssp(v); }
inline qreal sdpa(qreal v) { return Scope::global()->sdpa(v); }
inline qreal sdpi(qreal v) { return Scope::global()->sdpi(v); }
inline qreal hdp(qreal v) { return Scope::global()->hdp(v); }
inline qreal hsp(qreal v) { return Scope::global()->hsp(v); }
inline qreal hdpa(qreal v) { return Scope::global()->hdpa(v); }
inline qreal hdpi(qreal v) { return Scope::global()->hdpi(v); }
inline qreal wdp(qreal v) { return Scope::global()->wdp(v); }
inline qreal wsp(qreal v) { return Scope::global()->wsp(v); }
inline qreal wdpa(qreal v) { return Scope::global()->wdpa(v); }
inline qreal wdpi(qreal v) { return Scope::global()->wdpi(v); }
inline qreal asdp(qreal v) { return Scope::global()->asdp(v); }
inline qreal assp(qreal v) { return Scope::global()->assp(v); }
inline qreal asdpa(qreal v) { return Scope::global()->asdpa(v); }
inline qreal asdpi(qreal v) { return Scope::global()->asdpi(v); }
inline qreal ahdp(qreal v) { return Scope::global()->ahdp(v); }
inline qreal ahsp(qreal v) { return Scope::global()->ahsp(v); }
inline qreal ahdpa(qreal v) { return Scope::global()->ahdpa(v); }
inline qreal ahdpi(qreal v) { return Scope::global()->ahdpi(v); }
inline qreal awdp(qreal v) { return Scope::global()->awdp(v); }
inline qreal awsp(qreal v) { return Scope::global()->awsp(v); }
inline qreal awdpa(qreal v) { return Scope::global()->awdpa(v); }
inline qreal awdpi(qreal v) { return Scope::global()->awdpi(v); }
inline qreal psdp(qreal v) { return Scope::global()->psdp(v); }
inline qreal pssp(qreal v) { return Scope::global()->pssp(v); }
inline qreal psdpa(qreal v) { return Scope::global()->psdpa(v); }
inline qreal psdpi(qreal v) { return Scope::global()->psdpi(v); }
inline qreal phdp(qreal v) { return Scope::global()->phdp(v); }
inline qreal phsp(qreal v) { return Scope::global()->phsp(v); }
inline qreal phdpa(qreal v) { return Scope::global()->phdpa(v); }
inline qreal phdpi(qreal v) { return Scope::global()->phdpi(v); }
inline qreal pwdp(qreal v) { return Scope::global()->pwdp(v); }
inline qreal pwsp(qreal v) { return Scope::global()->pwsp(v); }
inline qreal pwdpa(qreal v) { return Scope::global()->pwdpa(v); }
inline qreal pwdpi(qreal v) { return Scope::global()->pwdpi(v); }
inline qreal pwsdp(qreal v) { return Scope::global()->pwsdp(v); }
inline qreal pwssp(qreal v) { return Scope::global()->pwssp(v); }
inline qreal pwsdpa(qreal v) { return Scope::global()->pwsdpa(v); }
inline qreal pwsdpi(qreal v) { return Scope::global()->pwsdpi(v); }
inline qreal pwhdp(qreal v) { return Scope::global()->pwhdp(v); }
inline qreal pwhsp(qreal v) { return Scope::global()->pwhsp(v); }
inline qreal pwhdpa(qreal v) { return Scope::global()->pwhdpa(v); }
inline qreal pwhdpi(qreal v) { return Scope::global()->pwhdpi(v); }
inline qreal pwwdp(qreal v) { return Scope::global()->pwwdp(v); }
inline qreal pwwsp(qreal v) { return Scope::global()->pwwsp(v); }
inline qreal pwwdpa(qreal v) { return Scope::global()->pwwdpa(v); }
inline qreal pwwdpi(qreal v) { return Scope::global()->pwwdpi(v); }
inline qreal fsdp(qreal v) { return Scope::global()->fsdp(v); }
inline qreal fssp(qreal v) { return Scope::global()->fssp(v); }
inline qreal fsdpa(qreal v) { return Scope::global()->fsdpa(v); }
inline qreal fsdpi(qreal v) { return Scope::global()->fsdpi(v); }
inline qreal fhdp(qreal v) { return Scope::global()->fhdp(v); }
inline qreal fhsp(qreal v) { return Scope::global()->fhsp(v); }
inline qreal fhdpa(qreal v) { return Scope::global()->fhdpa(v); }
inline qreal fhdpi(qreal v) { return Scope::global()->fhdpi(v); }
inline qreal fwdp(qreal v) { return Scope::global()->fwdp(v); }
inline qreal fwsp(qreal v) { return Scope::global()->fwsp(v); }
inline qreal fwdpa(qreal v) { return Scope::global()->fwdpa(v); }
inline qreal fwdpi(qreal v) { return Scope::global()->fwdpi(v); }
inline qreal isdp(qreal v) { return Scope::global()->isdp(v); }
inline qreal issp(qreal v) { return Scope::global()->issp(v); }
inline qreal isdpa(qreal v) { return Scope::global()->isdpa(v); }
inline qreal isdpi(qreal v) { return Scope::global()->isdpi(v); }
inline qreal ihdp(qreal v) { return Scope::global()->ihdp(v); }
inline qreal ihsp(qreal v) { return Scope::global()->ihsp(v); }
inline qreal ihdpa(qreal v) { return Scope::global()->ihdpa(v); }
inline qreal ihdpi(qreal v) { return Scope::global()->ihdpi(v); }
inline qreal iwdp(qreal v) { return Scope::global()->iwdp(v); }
inline qreal iwsp(qreal v) { return Scope::global()->iwsp(v); }
inline qreal iwdpa(qreal v) { return Scope::global()->iwdpa(v); }
inline qreal iwdpi(qreal v) { return Scope::global()->iwdpi(v); }
inline qreal logsdp(qreal v) { return Scope::global()->logsdp(v); }
inline qreal logssp(qreal v) { return Scope::global()->logssp(v); }
inline qreal logsdpa(qreal v) { return Scope::global()->logsdpa(v); }
inline qreal logsdpi(qreal v) { return Scope::global()->logsdpi(v); }
inline qreal loghdp(qreal v) { return Scope::global()->loghdp(v); }
inline qreal loghsp(qreal v) { return Scope::global()->loghsp(v); }
inline qreal loghdpa(qreal v) { return Scope::global()->loghdpa(v); }
inline qreal loghdpi(qreal v) { return Scope::global()->loghdpi(v); }
inline qreal logwdp(qreal v) { return Scope::global()->logwdp(v); }
inline qreal logwsp(qreal v) { return Scope::global()->logwsp(v); }
inline qreal logwdpa(qreal v) { return Scope::global()->logwdpa(v); }
inline qreal logwdpi(qreal v) { return Scope::global()->logwdpi(v); }
inline qreal dgsdp(qreal v) { return Scope::global()->dgsdp(v); }
inline qreal dgssp(qreal v) { return Scope::global()->dgssp(v); }
inline qreal dgsdpa(qreal v) { return Scope::global()->dgsdpa(v); }
inline qreal dgsdpi(qreal v) { return Scope::global()->dgsdpi(v); }
inline qreal dghdp(qreal v) { return Scope::global()->dghdp(v); }
inline qreal dghsp(qreal v) { return Scope::global()->dghsp(v); }
inline qreal dghdpa(qreal v) { return Scope::global()->dghdpa(v); }
inline qreal dghdpi(qreal v) { return Scope::global()->dghdpi(v); }
inline qreal dgwdp(qreal v) { return Scope::global()->dgwdp(v); }
inline qreal dgwsp(qreal v) { return Scope::global()->dgwsp(v); }
inline qreal dgwdpa(qreal v) { return Scope::global()->dgwdpa(v); }
inline qreal dgwdpi(qreal v) { return Scope::global()->dgwdpi(v); }
inline qreal prsdp(qreal v) { return Scope::global()->prsdp(v); }
inline qreal prssp(qreal v) { return Scope::global()->prssp(v); }
inline qreal prsdpa(qreal v) { return Scope::global()->prsdpa(v); }
inline qreal prsdpi(qreal v) { return Scope::global()->prsdpi(v); }
inline qreal prhdp(qreal v) { return Scope::global()->prhdp(v); }
inline qreal prhsp(qreal v) { return Scope::global()->prhsp(v); }
inline qreal prhdpa(qreal v) { return Scope::global()->prhdpa(v); }
inline qreal prhdpi(qreal v) { return Scope::global()->prhdpi(v); }
inline qreal prwdp(qreal v) { return Scope::global()->prwdp(v); }
inline qreal prwsp(qreal v) { return Scope::global()->prwsp(v); }
inline qreal prwdpa(qreal v) { return Scope::global()->prwdpa(v); }
inline qreal prwdpi(qreal v) { return Scope::global()->prwdpi(v); }
inline qreal ftsdp(qreal v) { return Scope::global()->ftsdp(v); }
inline qreal ftssp(qreal v) { return Scope::global()->ftssp(v); }
inline qreal ftsdpa(qreal v) { return Scope::global()->ftsdpa(v); }
inline qreal ftsdpi(qreal v) { return Scope::global()->ftsdpi(v); }
inline qreal fthdp(qreal v) { return Scope::global()->fthdp(v); }
inline qreal fthsp(qreal v) { return Scope::global()->fthsp(v); }
inline qreal fthdpa(qreal v) { return Scope::global()->fthdpa(v); }
inline qreal fthdpi(qreal v) { return Scope::global()->fthdpi(v); }
inline qreal ftwdp(qreal v) { return Scope::global()->ftwdp(v); }
inline qreal ftwsp(qreal v) { return Scope::global()->ftwsp(v); }
inline qreal ftwdpa(qreal v) { return Scope::global()->ftwdpa(v); }
inline qreal ftwdpi(qreal v) { return Scope::global()->ftwdpi(v); }
inline qreal flsdp(qreal v) { return Scope::global()->flsdp(v); }
inline qreal flssp(qreal v) { return Scope::global()->flssp(v); }
inline qreal flsdpa(qreal v) { return Scope::global()->flsdpa(v); }
inline qreal flsdpi(qreal v) { return Scope::global()->flsdpi(v); }
inline qreal flhdp(qreal v) { return Scope::global()->flhdp(v); }
inline qreal flhsp(qreal v) { return Scope::global()->flhsp(v); }
inline qreal flhdpa(qreal v) { return Scope::global()->flhdpa(v); }
inline qreal flhdpi(qreal v) { return Scope::global()->flhdpi(v); }
inline qreal flwdp(qreal v) { return Scope::global()->flwdp(v); }
inline qreal flwsp(qreal v) { return Scope::global()->flwsp(v); }
inline qreal flwdpa(qreal v) { return Scope::global()->flwdpa(v); }
inline qreal flwdpi(qreal v) { return Scope::global()->flwdpi(v); }
inline qreal dsdp(qreal v) { return Scope::global()->dsdp(v); }
inline qreal dssp(qreal v) { return Scope::global()->dssp(v); }
inline qreal dsdpa(qreal v) { return Scope::global()->dsdpa(v); }
inline qreal dsdpi(qreal v) { return Scope::global()->dsdpi(v); }
inline qreal dhdp(qreal v) { return Scope::global()->dhdp(v); }
inline qreal dhsp(qreal v) { return Scope::global()->dhsp(v); }
inline qreal dhdpa(qreal v) { return Scope::global()->dhdpa(v); }
inline qreal dhdpi(qreal v) { return Scope::global()->dhdpi(v); }
inline qreal dwdp(qreal v) { return Scope::global()->dwdp(v); }
inline qreal dwsp(qreal v) { return Scope::global()->dwsp(v); }
inline qreal dwdpa(qreal v) { return Scope::global()->dwdpa(v); }
inline qreal dwdpi(qreal v) { return Scope::global()->dwdpi(v); }
inline qreal sem(qreal v) { return Scope::global()->sem(v); }
inline qreal asem(qreal v) { return Scope::global()->asem(v); }
inline qreal sspa(qreal v) { return Scope::global()->sspa(v); }
inline qreal asspa(qreal v) { return Scope::global()->asspa(v); }
inline qreal hem(qreal v) { return Scope::global()->hem(v); }
inline qreal ahem(qreal v) { return Scope::global()->ahem(v); }
inline qreal hspa(qreal v) { return Scope::global()->hspa(v); }
inline qreal ahspa(qreal v) { return Scope::global()->ahspa(v); }
inline qreal wem(qreal v) { return Scope::global()->wem(v); }
inline qreal awem(qreal v) { return Scope::global()->awem(v); }
inline qreal wspa(qreal v) { return Scope::global()->wspa(v); }
inline qreal awspa(qreal v) { return Scope::global()->awspa(v); }
inline qreal sdpPh(qreal v) { return Scope::global()->sdpPh(v); }
inline qreal asdpPh(qreal v) { return Scope::global()->asdpPh(v); }
inline qreal sdpLh(qreal v) { return Scope::global()->sdpLh(v); }
inline qreal asdpLh(qreal v) { return Scope::global()->asdpLh(v); }
inline qreal sdpPw(qreal v) { return Scope::global()->sdpPw(v); }
inline qreal asdpPw(qreal v) { return Scope::global()->asdpPw(v); }
inline qreal sdpLw(qreal v) { return Scope::global()->sdpLw(v); }
inline qreal asdpLw(qreal v) { return Scope::global()->asdpLw(v); }
inline qreal hdpLw(qreal v) { return Scope::global()->hdpLw(v); }
inline qreal ahdpLw(qreal v) { return Scope::global()->ahdpLw(v); }
inline qreal hdpPw(qreal v) { return Scope::global()->hdpPw(v); }
inline qreal ahdpPw(qreal v) { return Scope::global()->ahdpPw(v); }
inline qreal wdpLh(qreal v) { return Scope::global()->wdpLh(v); }
inline qreal awdpLh(qreal v) { return Scope::global()->awdpLh(v); }
inline qreal wdpPh(qreal v) { return Scope::global()->wdpPh(v); }
inline qreal awdpPh(qreal v) { return Scope::global()->awdpPh(v); }

namespace literals {
// Literals over the global scope (logical px): 16_sdp, 14_ssp, 12.5_asdp, 120_ftsdp …
inline qreal operator""_sdp(unsigned long long v) { return Scope::global()->sdp(qreal(v)); }
inline qreal operator""_sdp(long double v) { return Scope::global()->sdp(qreal(v)); }
inline qreal operator""_ssp(unsigned long long v) { return Scope::global()->ssp(qreal(v)); }
inline qreal operator""_ssp(long double v) { return Scope::global()->ssp(qreal(v)); }
inline qreal operator""_sdpa(unsigned long long v) { return Scope::global()->sdpa(qreal(v)); }
inline qreal operator""_sdpa(long double v) { return Scope::global()->sdpa(qreal(v)); }
inline qreal operator""_sdpi(unsigned long long v) { return Scope::global()->sdpi(qreal(v)); }
inline qreal operator""_sdpi(long double v) { return Scope::global()->sdpi(qreal(v)); }
inline qreal operator""_hdp(unsigned long long v) { return Scope::global()->hdp(qreal(v)); }
inline qreal operator""_hdp(long double v) { return Scope::global()->hdp(qreal(v)); }
inline qreal operator""_hsp(unsigned long long v) { return Scope::global()->hsp(qreal(v)); }
inline qreal operator""_hsp(long double v) { return Scope::global()->hsp(qreal(v)); }
inline qreal operator""_hdpa(unsigned long long v) { return Scope::global()->hdpa(qreal(v)); }
inline qreal operator""_hdpa(long double v) { return Scope::global()->hdpa(qreal(v)); }
inline qreal operator""_hdpi(unsigned long long v) { return Scope::global()->hdpi(qreal(v)); }
inline qreal operator""_hdpi(long double v) { return Scope::global()->hdpi(qreal(v)); }
inline qreal operator""_wdp(unsigned long long v) { return Scope::global()->wdp(qreal(v)); }
inline qreal operator""_wdp(long double v) { return Scope::global()->wdp(qreal(v)); }
inline qreal operator""_wsp(unsigned long long v) { return Scope::global()->wsp(qreal(v)); }
inline qreal operator""_wsp(long double v) { return Scope::global()->wsp(qreal(v)); }
inline qreal operator""_wdpa(unsigned long long v) { return Scope::global()->wdpa(qreal(v)); }
inline qreal operator""_wdpa(long double v) { return Scope::global()->wdpa(qreal(v)); }
inline qreal operator""_wdpi(unsigned long long v) { return Scope::global()->wdpi(qreal(v)); }
inline qreal operator""_wdpi(long double v) { return Scope::global()->wdpi(qreal(v)); }
inline qreal operator""_asdp(unsigned long long v) { return Scope::global()->asdp(qreal(v)); }
inline qreal operator""_asdp(long double v) { return Scope::global()->asdp(qreal(v)); }
inline qreal operator""_assp(unsigned long long v) { return Scope::global()->assp(qreal(v)); }
inline qreal operator""_assp(long double v) { return Scope::global()->assp(qreal(v)); }
inline qreal operator""_asdpa(unsigned long long v) { return Scope::global()->asdpa(qreal(v)); }
inline qreal operator""_asdpa(long double v) { return Scope::global()->asdpa(qreal(v)); }
inline qreal operator""_asdpi(unsigned long long v) { return Scope::global()->asdpi(qreal(v)); }
inline qreal operator""_asdpi(long double v) { return Scope::global()->asdpi(qreal(v)); }
inline qreal operator""_ahdp(unsigned long long v) { return Scope::global()->ahdp(qreal(v)); }
inline qreal operator""_ahdp(long double v) { return Scope::global()->ahdp(qreal(v)); }
inline qreal operator""_ahsp(unsigned long long v) { return Scope::global()->ahsp(qreal(v)); }
inline qreal operator""_ahsp(long double v) { return Scope::global()->ahsp(qreal(v)); }
inline qreal operator""_ahdpa(unsigned long long v) { return Scope::global()->ahdpa(qreal(v)); }
inline qreal operator""_ahdpa(long double v) { return Scope::global()->ahdpa(qreal(v)); }
inline qreal operator""_ahdpi(unsigned long long v) { return Scope::global()->ahdpi(qreal(v)); }
inline qreal operator""_ahdpi(long double v) { return Scope::global()->ahdpi(qreal(v)); }
inline qreal operator""_awdp(unsigned long long v) { return Scope::global()->awdp(qreal(v)); }
inline qreal operator""_awdp(long double v) { return Scope::global()->awdp(qreal(v)); }
inline qreal operator""_awsp(unsigned long long v) { return Scope::global()->awsp(qreal(v)); }
inline qreal operator""_awsp(long double v) { return Scope::global()->awsp(qreal(v)); }
inline qreal operator""_awdpa(unsigned long long v) { return Scope::global()->awdpa(qreal(v)); }
inline qreal operator""_awdpa(long double v) { return Scope::global()->awdpa(qreal(v)); }
inline qreal operator""_awdpi(unsigned long long v) { return Scope::global()->awdpi(qreal(v)); }
inline qreal operator""_awdpi(long double v) { return Scope::global()->awdpi(qreal(v)); }
inline qreal operator""_psdp(unsigned long long v) { return Scope::global()->psdp(qreal(v)); }
inline qreal operator""_psdp(long double v) { return Scope::global()->psdp(qreal(v)); }
inline qreal operator""_pssp(unsigned long long v) { return Scope::global()->pssp(qreal(v)); }
inline qreal operator""_pssp(long double v) { return Scope::global()->pssp(qreal(v)); }
inline qreal operator""_psdpa(unsigned long long v) { return Scope::global()->psdpa(qreal(v)); }
inline qreal operator""_psdpa(long double v) { return Scope::global()->psdpa(qreal(v)); }
inline qreal operator""_psdpi(unsigned long long v) { return Scope::global()->psdpi(qreal(v)); }
inline qreal operator""_psdpi(long double v) { return Scope::global()->psdpi(qreal(v)); }
inline qreal operator""_phdp(unsigned long long v) { return Scope::global()->phdp(qreal(v)); }
inline qreal operator""_phdp(long double v) { return Scope::global()->phdp(qreal(v)); }
inline qreal operator""_phsp(unsigned long long v) { return Scope::global()->phsp(qreal(v)); }
inline qreal operator""_phsp(long double v) { return Scope::global()->phsp(qreal(v)); }
inline qreal operator""_phdpa(unsigned long long v) { return Scope::global()->phdpa(qreal(v)); }
inline qreal operator""_phdpa(long double v) { return Scope::global()->phdpa(qreal(v)); }
inline qreal operator""_phdpi(unsigned long long v) { return Scope::global()->phdpi(qreal(v)); }
inline qreal operator""_phdpi(long double v) { return Scope::global()->phdpi(qreal(v)); }
inline qreal operator""_pwdp(unsigned long long v) { return Scope::global()->pwdp(qreal(v)); }
inline qreal operator""_pwdp(long double v) { return Scope::global()->pwdp(qreal(v)); }
inline qreal operator""_pwsp(unsigned long long v) { return Scope::global()->pwsp(qreal(v)); }
inline qreal operator""_pwsp(long double v) { return Scope::global()->pwsp(qreal(v)); }
inline qreal operator""_pwdpa(unsigned long long v) { return Scope::global()->pwdpa(qreal(v)); }
inline qreal operator""_pwdpa(long double v) { return Scope::global()->pwdpa(qreal(v)); }
inline qreal operator""_pwdpi(unsigned long long v) { return Scope::global()->pwdpi(qreal(v)); }
inline qreal operator""_pwdpi(long double v) { return Scope::global()->pwdpi(qreal(v)); }
inline qreal operator""_pwsdp(unsigned long long v) { return Scope::global()->pwsdp(qreal(v)); }
inline qreal operator""_pwsdp(long double v) { return Scope::global()->pwsdp(qreal(v)); }
inline qreal operator""_pwssp(unsigned long long v) { return Scope::global()->pwssp(qreal(v)); }
inline qreal operator""_pwssp(long double v) { return Scope::global()->pwssp(qreal(v)); }
inline qreal operator""_pwsdpa(unsigned long long v) { return Scope::global()->pwsdpa(qreal(v)); }
inline qreal operator""_pwsdpa(long double v) { return Scope::global()->pwsdpa(qreal(v)); }
inline qreal operator""_pwsdpi(unsigned long long v) { return Scope::global()->pwsdpi(qreal(v)); }
inline qreal operator""_pwsdpi(long double v) { return Scope::global()->pwsdpi(qreal(v)); }
inline qreal operator""_pwhdp(unsigned long long v) { return Scope::global()->pwhdp(qreal(v)); }
inline qreal operator""_pwhdp(long double v) { return Scope::global()->pwhdp(qreal(v)); }
inline qreal operator""_pwhsp(unsigned long long v) { return Scope::global()->pwhsp(qreal(v)); }
inline qreal operator""_pwhsp(long double v) { return Scope::global()->pwhsp(qreal(v)); }
inline qreal operator""_pwhdpa(unsigned long long v) { return Scope::global()->pwhdpa(qreal(v)); }
inline qreal operator""_pwhdpa(long double v) { return Scope::global()->pwhdpa(qreal(v)); }
inline qreal operator""_pwhdpi(unsigned long long v) { return Scope::global()->pwhdpi(qreal(v)); }
inline qreal operator""_pwhdpi(long double v) { return Scope::global()->pwhdpi(qreal(v)); }
inline qreal operator""_pwwdp(unsigned long long v) { return Scope::global()->pwwdp(qreal(v)); }
inline qreal operator""_pwwdp(long double v) { return Scope::global()->pwwdp(qreal(v)); }
inline qreal operator""_pwwsp(unsigned long long v) { return Scope::global()->pwwsp(qreal(v)); }
inline qreal operator""_pwwsp(long double v) { return Scope::global()->pwwsp(qreal(v)); }
inline qreal operator""_pwwdpa(unsigned long long v) { return Scope::global()->pwwdpa(qreal(v)); }
inline qreal operator""_pwwdpa(long double v) { return Scope::global()->pwwdpa(qreal(v)); }
inline qreal operator""_pwwdpi(unsigned long long v) { return Scope::global()->pwwdpi(qreal(v)); }
inline qreal operator""_pwwdpi(long double v) { return Scope::global()->pwwdpi(qreal(v)); }
inline qreal operator""_fsdp(unsigned long long v) { return Scope::global()->fsdp(qreal(v)); }
inline qreal operator""_fsdp(long double v) { return Scope::global()->fsdp(qreal(v)); }
inline qreal operator""_fssp(unsigned long long v) { return Scope::global()->fssp(qreal(v)); }
inline qreal operator""_fssp(long double v) { return Scope::global()->fssp(qreal(v)); }
inline qreal operator""_fsdpa(unsigned long long v) { return Scope::global()->fsdpa(qreal(v)); }
inline qreal operator""_fsdpa(long double v) { return Scope::global()->fsdpa(qreal(v)); }
inline qreal operator""_fsdpi(unsigned long long v) { return Scope::global()->fsdpi(qreal(v)); }
inline qreal operator""_fsdpi(long double v) { return Scope::global()->fsdpi(qreal(v)); }
inline qreal operator""_fhdp(unsigned long long v) { return Scope::global()->fhdp(qreal(v)); }
inline qreal operator""_fhdp(long double v) { return Scope::global()->fhdp(qreal(v)); }
inline qreal operator""_fhsp(unsigned long long v) { return Scope::global()->fhsp(qreal(v)); }
inline qreal operator""_fhsp(long double v) { return Scope::global()->fhsp(qreal(v)); }
inline qreal operator""_fhdpa(unsigned long long v) { return Scope::global()->fhdpa(qreal(v)); }
inline qreal operator""_fhdpa(long double v) { return Scope::global()->fhdpa(qreal(v)); }
inline qreal operator""_fhdpi(unsigned long long v) { return Scope::global()->fhdpi(qreal(v)); }
inline qreal operator""_fhdpi(long double v) { return Scope::global()->fhdpi(qreal(v)); }
inline qreal operator""_fwdp(unsigned long long v) { return Scope::global()->fwdp(qreal(v)); }
inline qreal operator""_fwdp(long double v) { return Scope::global()->fwdp(qreal(v)); }
inline qreal operator""_fwsp(unsigned long long v) { return Scope::global()->fwsp(qreal(v)); }
inline qreal operator""_fwsp(long double v) { return Scope::global()->fwsp(qreal(v)); }
inline qreal operator""_fwdpa(unsigned long long v) { return Scope::global()->fwdpa(qreal(v)); }
inline qreal operator""_fwdpa(long double v) { return Scope::global()->fwdpa(qreal(v)); }
inline qreal operator""_fwdpi(unsigned long long v) { return Scope::global()->fwdpi(qreal(v)); }
inline qreal operator""_fwdpi(long double v) { return Scope::global()->fwdpi(qreal(v)); }
inline qreal operator""_isdp(unsigned long long v) { return Scope::global()->isdp(qreal(v)); }
inline qreal operator""_isdp(long double v) { return Scope::global()->isdp(qreal(v)); }
inline qreal operator""_issp(unsigned long long v) { return Scope::global()->issp(qreal(v)); }
inline qreal operator""_issp(long double v) { return Scope::global()->issp(qreal(v)); }
inline qreal operator""_isdpa(unsigned long long v) { return Scope::global()->isdpa(qreal(v)); }
inline qreal operator""_isdpa(long double v) { return Scope::global()->isdpa(qreal(v)); }
inline qreal operator""_isdpi(unsigned long long v) { return Scope::global()->isdpi(qreal(v)); }
inline qreal operator""_isdpi(long double v) { return Scope::global()->isdpi(qreal(v)); }
inline qreal operator""_ihdp(unsigned long long v) { return Scope::global()->ihdp(qreal(v)); }
inline qreal operator""_ihdp(long double v) { return Scope::global()->ihdp(qreal(v)); }
inline qreal operator""_ihsp(unsigned long long v) { return Scope::global()->ihsp(qreal(v)); }
inline qreal operator""_ihsp(long double v) { return Scope::global()->ihsp(qreal(v)); }
inline qreal operator""_ihdpa(unsigned long long v) { return Scope::global()->ihdpa(qreal(v)); }
inline qreal operator""_ihdpa(long double v) { return Scope::global()->ihdpa(qreal(v)); }
inline qreal operator""_ihdpi(unsigned long long v) { return Scope::global()->ihdpi(qreal(v)); }
inline qreal operator""_ihdpi(long double v) { return Scope::global()->ihdpi(qreal(v)); }
inline qreal operator""_iwdp(unsigned long long v) { return Scope::global()->iwdp(qreal(v)); }
inline qreal operator""_iwdp(long double v) { return Scope::global()->iwdp(qreal(v)); }
inline qreal operator""_iwsp(unsigned long long v) { return Scope::global()->iwsp(qreal(v)); }
inline qreal operator""_iwsp(long double v) { return Scope::global()->iwsp(qreal(v)); }
inline qreal operator""_iwdpa(unsigned long long v) { return Scope::global()->iwdpa(qreal(v)); }
inline qreal operator""_iwdpa(long double v) { return Scope::global()->iwdpa(qreal(v)); }
inline qreal operator""_iwdpi(unsigned long long v) { return Scope::global()->iwdpi(qreal(v)); }
inline qreal operator""_iwdpi(long double v) { return Scope::global()->iwdpi(qreal(v)); }
inline qreal operator""_logsdp(unsigned long long v) { return Scope::global()->logsdp(qreal(v)); }
inline qreal operator""_logsdp(long double v) { return Scope::global()->logsdp(qreal(v)); }
inline qreal operator""_logssp(unsigned long long v) { return Scope::global()->logssp(qreal(v)); }
inline qreal operator""_logssp(long double v) { return Scope::global()->logssp(qreal(v)); }
inline qreal operator""_logsdpa(unsigned long long v) { return Scope::global()->logsdpa(qreal(v)); }
inline qreal operator""_logsdpa(long double v) { return Scope::global()->logsdpa(qreal(v)); }
inline qreal operator""_logsdpi(unsigned long long v) { return Scope::global()->logsdpi(qreal(v)); }
inline qreal operator""_logsdpi(long double v) { return Scope::global()->logsdpi(qreal(v)); }
inline qreal operator""_loghdp(unsigned long long v) { return Scope::global()->loghdp(qreal(v)); }
inline qreal operator""_loghdp(long double v) { return Scope::global()->loghdp(qreal(v)); }
inline qreal operator""_loghsp(unsigned long long v) { return Scope::global()->loghsp(qreal(v)); }
inline qreal operator""_loghsp(long double v) { return Scope::global()->loghsp(qreal(v)); }
inline qreal operator""_loghdpa(unsigned long long v) { return Scope::global()->loghdpa(qreal(v)); }
inline qreal operator""_loghdpa(long double v) { return Scope::global()->loghdpa(qreal(v)); }
inline qreal operator""_loghdpi(unsigned long long v) { return Scope::global()->loghdpi(qreal(v)); }
inline qreal operator""_loghdpi(long double v) { return Scope::global()->loghdpi(qreal(v)); }
inline qreal operator""_logwdp(unsigned long long v) { return Scope::global()->logwdp(qreal(v)); }
inline qreal operator""_logwdp(long double v) { return Scope::global()->logwdp(qreal(v)); }
inline qreal operator""_logwsp(unsigned long long v) { return Scope::global()->logwsp(qreal(v)); }
inline qreal operator""_logwsp(long double v) { return Scope::global()->logwsp(qreal(v)); }
inline qreal operator""_logwdpa(unsigned long long v) { return Scope::global()->logwdpa(qreal(v)); }
inline qreal operator""_logwdpa(long double v) { return Scope::global()->logwdpa(qreal(v)); }
inline qreal operator""_logwdpi(unsigned long long v) { return Scope::global()->logwdpi(qreal(v)); }
inline qreal operator""_logwdpi(long double v) { return Scope::global()->logwdpi(qreal(v)); }
inline qreal operator""_dgsdp(unsigned long long v) { return Scope::global()->dgsdp(qreal(v)); }
inline qreal operator""_dgsdp(long double v) { return Scope::global()->dgsdp(qreal(v)); }
inline qreal operator""_dgssp(unsigned long long v) { return Scope::global()->dgssp(qreal(v)); }
inline qreal operator""_dgssp(long double v) { return Scope::global()->dgssp(qreal(v)); }
inline qreal operator""_dgsdpa(unsigned long long v) { return Scope::global()->dgsdpa(qreal(v)); }
inline qreal operator""_dgsdpa(long double v) { return Scope::global()->dgsdpa(qreal(v)); }
inline qreal operator""_dgsdpi(unsigned long long v) { return Scope::global()->dgsdpi(qreal(v)); }
inline qreal operator""_dgsdpi(long double v) { return Scope::global()->dgsdpi(qreal(v)); }
inline qreal operator""_dghdp(unsigned long long v) { return Scope::global()->dghdp(qreal(v)); }
inline qreal operator""_dghdp(long double v) { return Scope::global()->dghdp(qreal(v)); }
inline qreal operator""_dghsp(unsigned long long v) { return Scope::global()->dghsp(qreal(v)); }
inline qreal operator""_dghsp(long double v) { return Scope::global()->dghsp(qreal(v)); }
inline qreal operator""_dghdpa(unsigned long long v) { return Scope::global()->dghdpa(qreal(v)); }
inline qreal operator""_dghdpa(long double v) { return Scope::global()->dghdpa(qreal(v)); }
inline qreal operator""_dghdpi(unsigned long long v) { return Scope::global()->dghdpi(qreal(v)); }
inline qreal operator""_dghdpi(long double v) { return Scope::global()->dghdpi(qreal(v)); }
inline qreal operator""_dgwdp(unsigned long long v) { return Scope::global()->dgwdp(qreal(v)); }
inline qreal operator""_dgwdp(long double v) { return Scope::global()->dgwdp(qreal(v)); }
inline qreal operator""_dgwsp(unsigned long long v) { return Scope::global()->dgwsp(qreal(v)); }
inline qreal operator""_dgwsp(long double v) { return Scope::global()->dgwsp(qreal(v)); }
inline qreal operator""_dgwdpa(unsigned long long v) { return Scope::global()->dgwdpa(qreal(v)); }
inline qreal operator""_dgwdpa(long double v) { return Scope::global()->dgwdpa(qreal(v)); }
inline qreal operator""_dgwdpi(unsigned long long v) { return Scope::global()->dgwdpi(qreal(v)); }
inline qreal operator""_dgwdpi(long double v) { return Scope::global()->dgwdpi(qreal(v)); }
inline qreal operator""_prsdp(unsigned long long v) { return Scope::global()->prsdp(qreal(v)); }
inline qreal operator""_prsdp(long double v) { return Scope::global()->prsdp(qreal(v)); }
inline qreal operator""_prssp(unsigned long long v) { return Scope::global()->prssp(qreal(v)); }
inline qreal operator""_prssp(long double v) { return Scope::global()->prssp(qreal(v)); }
inline qreal operator""_prsdpa(unsigned long long v) { return Scope::global()->prsdpa(qreal(v)); }
inline qreal operator""_prsdpa(long double v) { return Scope::global()->prsdpa(qreal(v)); }
inline qreal operator""_prsdpi(unsigned long long v) { return Scope::global()->prsdpi(qreal(v)); }
inline qreal operator""_prsdpi(long double v) { return Scope::global()->prsdpi(qreal(v)); }
inline qreal operator""_prhdp(unsigned long long v) { return Scope::global()->prhdp(qreal(v)); }
inline qreal operator""_prhdp(long double v) { return Scope::global()->prhdp(qreal(v)); }
inline qreal operator""_prhsp(unsigned long long v) { return Scope::global()->prhsp(qreal(v)); }
inline qreal operator""_prhsp(long double v) { return Scope::global()->prhsp(qreal(v)); }
inline qreal operator""_prhdpa(unsigned long long v) { return Scope::global()->prhdpa(qreal(v)); }
inline qreal operator""_prhdpa(long double v) { return Scope::global()->prhdpa(qreal(v)); }
inline qreal operator""_prhdpi(unsigned long long v) { return Scope::global()->prhdpi(qreal(v)); }
inline qreal operator""_prhdpi(long double v) { return Scope::global()->prhdpi(qreal(v)); }
inline qreal operator""_prwdp(unsigned long long v) { return Scope::global()->prwdp(qreal(v)); }
inline qreal operator""_prwdp(long double v) { return Scope::global()->prwdp(qreal(v)); }
inline qreal operator""_prwsp(unsigned long long v) { return Scope::global()->prwsp(qreal(v)); }
inline qreal operator""_prwsp(long double v) { return Scope::global()->prwsp(qreal(v)); }
inline qreal operator""_prwdpa(unsigned long long v) { return Scope::global()->prwdpa(qreal(v)); }
inline qreal operator""_prwdpa(long double v) { return Scope::global()->prwdpa(qreal(v)); }
inline qreal operator""_prwdpi(unsigned long long v) { return Scope::global()->prwdpi(qreal(v)); }
inline qreal operator""_prwdpi(long double v) { return Scope::global()->prwdpi(qreal(v)); }
inline qreal operator""_ftsdp(unsigned long long v) { return Scope::global()->ftsdp(qreal(v)); }
inline qreal operator""_ftsdp(long double v) { return Scope::global()->ftsdp(qreal(v)); }
inline qreal operator""_ftssp(unsigned long long v) { return Scope::global()->ftssp(qreal(v)); }
inline qreal operator""_ftssp(long double v) { return Scope::global()->ftssp(qreal(v)); }
inline qreal operator""_ftsdpa(unsigned long long v) { return Scope::global()->ftsdpa(qreal(v)); }
inline qreal operator""_ftsdpa(long double v) { return Scope::global()->ftsdpa(qreal(v)); }
inline qreal operator""_ftsdpi(unsigned long long v) { return Scope::global()->ftsdpi(qreal(v)); }
inline qreal operator""_ftsdpi(long double v) { return Scope::global()->ftsdpi(qreal(v)); }
inline qreal operator""_fthdp(unsigned long long v) { return Scope::global()->fthdp(qreal(v)); }
inline qreal operator""_fthdp(long double v) { return Scope::global()->fthdp(qreal(v)); }
inline qreal operator""_fthsp(unsigned long long v) { return Scope::global()->fthsp(qreal(v)); }
inline qreal operator""_fthsp(long double v) { return Scope::global()->fthsp(qreal(v)); }
inline qreal operator""_fthdpa(unsigned long long v) { return Scope::global()->fthdpa(qreal(v)); }
inline qreal operator""_fthdpa(long double v) { return Scope::global()->fthdpa(qreal(v)); }
inline qreal operator""_fthdpi(unsigned long long v) { return Scope::global()->fthdpi(qreal(v)); }
inline qreal operator""_fthdpi(long double v) { return Scope::global()->fthdpi(qreal(v)); }
inline qreal operator""_ftwdp(unsigned long long v) { return Scope::global()->ftwdp(qreal(v)); }
inline qreal operator""_ftwdp(long double v) { return Scope::global()->ftwdp(qreal(v)); }
inline qreal operator""_ftwsp(unsigned long long v) { return Scope::global()->ftwsp(qreal(v)); }
inline qreal operator""_ftwsp(long double v) { return Scope::global()->ftwsp(qreal(v)); }
inline qreal operator""_ftwdpa(unsigned long long v) { return Scope::global()->ftwdpa(qreal(v)); }
inline qreal operator""_ftwdpa(long double v) { return Scope::global()->ftwdpa(qreal(v)); }
inline qreal operator""_ftwdpi(unsigned long long v) { return Scope::global()->ftwdpi(qreal(v)); }
inline qreal operator""_ftwdpi(long double v) { return Scope::global()->ftwdpi(qreal(v)); }
inline qreal operator""_flsdp(unsigned long long v) { return Scope::global()->flsdp(qreal(v)); }
inline qreal operator""_flsdp(long double v) { return Scope::global()->flsdp(qreal(v)); }
inline qreal operator""_flssp(unsigned long long v) { return Scope::global()->flssp(qreal(v)); }
inline qreal operator""_flssp(long double v) { return Scope::global()->flssp(qreal(v)); }
inline qreal operator""_flsdpa(unsigned long long v) { return Scope::global()->flsdpa(qreal(v)); }
inline qreal operator""_flsdpa(long double v) { return Scope::global()->flsdpa(qreal(v)); }
inline qreal operator""_flsdpi(unsigned long long v) { return Scope::global()->flsdpi(qreal(v)); }
inline qreal operator""_flsdpi(long double v) { return Scope::global()->flsdpi(qreal(v)); }
inline qreal operator""_flhdp(unsigned long long v) { return Scope::global()->flhdp(qreal(v)); }
inline qreal operator""_flhdp(long double v) { return Scope::global()->flhdp(qreal(v)); }
inline qreal operator""_flhsp(unsigned long long v) { return Scope::global()->flhsp(qreal(v)); }
inline qreal operator""_flhsp(long double v) { return Scope::global()->flhsp(qreal(v)); }
inline qreal operator""_flhdpa(unsigned long long v) { return Scope::global()->flhdpa(qreal(v)); }
inline qreal operator""_flhdpa(long double v) { return Scope::global()->flhdpa(qreal(v)); }
inline qreal operator""_flhdpi(unsigned long long v) { return Scope::global()->flhdpi(qreal(v)); }
inline qreal operator""_flhdpi(long double v) { return Scope::global()->flhdpi(qreal(v)); }
inline qreal operator""_flwdp(unsigned long long v) { return Scope::global()->flwdp(qreal(v)); }
inline qreal operator""_flwdp(long double v) { return Scope::global()->flwdp(qreal(v)); }
inline qreal operator""_flwsp(unsigned long long v) { return Scope::global()->flwsp(qreal(v)); }
inline qreal operator""_flwsp(long double v) { return Scope::global()->flwsp(qreal(v)); }
inline qreal operator""_flwdpa(unsigned long long v) { return Scope::global()->flwdpa(qreal(v)); }
inline qreal operator""_flwdpa(long double v) { return Scope::global()->flwdpa(qreal(v)); }
inline qreal operator""_flwdpi(unsigned long long v) { return Scope::global()->flwdpi(qreal(v)); }
inline qreal operator""_flwdpi(long double v) { return Scope::global()->flwdpi(qreal(v)); }
inline qreal operator""_dsdp(unsigned long long v) { return Scope::global()->dsdp(qreal(v)); }
inline qreal operator""_dsdp(long double v) { return Scope::global()->dsdp(qreal(v)); }
inline qreal operator""_dssp(unsigned long long v) { return Scope::global()->dssp(qreal(v)); }
inline qreal operator""_dssp(long double v) { return Scope::global()->dssp(qreal(v)); }
inline qreal operator""_dsdpa(unsigned long long v) { return Scope::global()->dsdpa(qreal(v)); }
inline qreal operator""_dsdpa(long double v) { return Scope::global()->dsdpa(qreal(v)); }
inline qreal operator""_dsdpi(unsigned long long v) { return Scope::global()->dsdpi(qreal(v)); }
inline qreal operator""_dsdpi(long double v) { return Scope::global()->dsdpi(qreal(v)); }
inline qreal operator""_dhdp(unsigned long long v) { return Scope::global()->dhdp(qreal(v)); }
inline qreal operator""_dhdp(long double v) { return Scope::global()->dhdp(qreal(v)); }
inline qreal operator""_dhsp(unsigned long long v) { return Scope::global()->dhsp(qreal(v)); }
inline qreal operator""_dhsp(long double v) { return Scope::global()->dhsp(qreal(v)); }
inline qreal operator""_dhdpa(unsigned long long v) { return Scope::global()->dhdpa(qreal(v)); }
inline qreal operator""_dhdpa(long double v) { return Scope::global()->dhdpa(qreal(v)); }
inline qreal operator""_dhdpi(unsigned long long v) { return Scope::global()->dhdpi(qreal(v)); }
inline qreal operator""_dhdpi(long double v) { return Scope::global()->dhdpi(qreal(v)); }
inline qreal operator""_dwdp(unsigned long long v) { return Scope::global()->dwdp(qreal(v)); }
inline qreal operator""_dwdp(long double v) { return Scope::global()->dwdp(qreal(v)); }
inline qreal operator""_dwsp(unsigned long long v) { return Scope::global()->dwsp(qreal(v)); }
inline qreal operator""_dwsp(long double v) { return Scope::global()->dwsp(qreal(v)); }
inline qreal operator""_dwdpa(unsigned long long v) { return Scope::global()->dwdpa(qreal(v)); }
inline qreal operator""_dwdpa(long double v) { return Scope::global()->dwdpa(qreal(v)); }
inline qreal operator""_dwdpi(unsigned long long v) { return Scope::global()->dwdpi(qreal(v)); }
inline qreal operator""_dwdpi(long double v) { return Scope::global()->dwdpi(qreal(v)); }
inline qreal operator""_sem(unsigned long long v) { return Scope::global()->sem(qreal(v)); }
inline qreal operator""_sem(long double v) { return Scope::global()->sem(qreal(v)); }
inline qreal operator""_asem(unsigned long long v) { return Scope::global()->asem(qreal(v)); }
inline qreal operator""_asem(long double v) { return Scope::global()->asem(qreal(v)); }
inline qreal operator""_sspa(unsigned long long v) { return Scope::global()->sspa(qreal(v)); }
inline qreal operator""_sspa(long double v) { return Scope::global()->sspa(qreal(v)); }
inline qreal operator""_asspa(unsigned long long v) { return Scope::global()->asspa(qreal(v)); }
inline qreal operator""_asspa(long double v) { return Scope::global()->asspa(qreal(v)); }
inline qreal operator""_hem(unsigned long long v) { return Scope::global()->hem(qreal(v)); }
inline qreal operator""_hem(long double v) { return Scope::global()->hem(qreal(v)); }
inline qreal operator""_ahem(unsigned long long v) { return Scope::global()->ahem(qreal(v)); }
inline qreal operator""_ahem(long double v) { return Scope::global()->ahem(qreal(v)); }
inline qreal operator""_hspa(unsigned long long v) { return Scope::global()->hspa(qreal(v)); }
inline qreal operator""_hspa(long double v) { return Scope::global()->hspa(qreal(v)); }
inline qreal operator""_ahspa(unsigned long long v) { return Scope::global()->ahspa(qreal(v)); }
inline qreal operator""_ahspa(long double v) { return Scope::global()->ahspa(qreal(v)); }
inline qreal operator""_wem(unsigned long long v) { return Scope::global()->wem(qreal(v)); }
inline qreal operator""_wem(long double v) { return Scope::global()->wem(qreal(v)); }
inline qreal operator""_awem(unsigned long long v) { return Scope::global()->awem(qreal(v)); }
inline qreal operator""_awem(long double v) { return Scope::global()->awem(qreal(v)); }
inline qreal operator""_wspa(unsigned long long v) { return Scope::global()->wspa(qreal(v)); }
inline qreal operator""_wspa(long double v) { return Scope::global()->wspa(qreal(v)); }
inline qreal operator""_awspa(unsigned long long v) { return Scope::global()->awspa(qreal(v)); }
inline qreal operator""_awspa(long double v) { return Scope::global()->awspa(qreal(v)); }
inline qreal operator""_sdpPh(unsigned long long v) { return Scope::global()->sdpPh(qreal(v)); }
inline qreal operator""_sdpPh(long double v) { return Scope::global()->sdpPh(qreal(v)); }
inline qreal operator""_asdpPh(unsigned long long v) { return Scope::global()->asdpPh(qreal(v)); }
inline qreal operator""_asdpPh(long double v) { return Scope::global()->asdpPh(qreal(v)); }
inline qreal operator""_sdpLh(unsigned long long v) { return Scope::global()->sdpLh(qreal(v)); }
inline qreal operator""_sdpLh(long double v) { return Scope::global()->sdpLh(qreal(v)); }
inline qreal operator""_asdpLh(unsigned long long v) { return Scope::global()->asdpLh(qreal(v)); }
inline qreal operator""_asdpLh(long double v) { return Scope::global()->asdpLh(qreal(v)); }
inline qreal operator""_sdpPw(unsigned long long v) { return Scope::global()->sdpPw(qreal(v)); }
inline qreal operator""_sdpPw(long double v) { return Scope::global()->sdpPw(qreal(v)); }
inline qreal operator""_asdpPw(unsigned long long v) { return Scope::global()->asdpPw(qreal(v)); }
inline qreal operator""_asdpPw(long double v) { return Scope::global()->asdpPw(qreal(v)); }
inline qreal operator""_sdpLw(unsigned long long v) { return Scope::global()->sdpLw(qreal(v)); }
inline qreal operator""_sdpLw(long double v) { return Scope::global()->sdpLw(qreal(v)); }
inline qreal operator""_asdpLw(unsigned long long v) { return Scope::global()->asdpLw(qreal(v)); }
inline qreal operator""_asdpLw(long double v) { return Scope::global()->asdpLw(qreal(v)); }
inline qreal operator""_hdpLw(unsigned long long v) { return Scope::global()->hdpLw(qreal(v)); }
inline qreal operator""_hdpLw(long double v) { return Scope::global()->hdpLw(qreal(v)); }
inline qreal operator""_ahdpLw(unsigned long long v) { return Scope::global()->ahdpLw(qreal(v)); }
inline qreal operator""_ahdpLw(long double v) { return Scope::global()->ahdpLw(qreal(v)); }
inline qreal operator""_hdpPw(unsigned long long v) { return Scope::global()->hdpPw(qreal(v)); }
inline qreal operator""_hdpPw(long double v) { return Scope::global()->hdpPw(qreal(v)); }
inline qreal operator""_ahdpPw(unsigned long long v) { return Scope::global()->ahdpPw(qreal(v)); }
inline qreal operator""_ahdpPw(long double v) { return Scope::global()->ahdpPw(qreal(v)); }
inline qreal operator""_wdpLh(unsigned long long v) { return Scope::global()->wdpLh(qreal(v)); }
inline qreal operator""_wdpLh(long double v) { return Scope::global()->wdpLh(qreal(v)); }
inline qreal operator""_awdpLh(unsigned long long v) { return Scope::global()->awdpLh(qreal(v)); }
inline qreal operator""_awdpLh(long double v) { return Scope::global()->awdpLh(qreal(v)); }
inline qreal operator""_wdpPh(unsigned long long v) { return Scope::global()->wdpPh(qreal(v)); }
inline qreal operator""_wdpPh(long double v) { return Scope::global()->wdpPh(qreal(v)); }
inline qreal operator""_awdpPh(unsigned long long v) { return Scope::global()->awdpPh(qreal(v)); }
inline qreal operator""_awdpPh(long double v) { return Scope::global()->awdpPh(qreal(v)); }
} // namespace literals
    // </generated-free>

} // namespace AppDimens
