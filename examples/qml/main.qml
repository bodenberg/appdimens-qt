import QtQuick 2.12
import QtQuick.Window 2.12
import AppDimens 1.0

Window {
    id: win
    visible: true
    width: 400; height: 700
    // Per-window scope (multi-monitor aware). The singleton `AppDimens` follows the first window.
    DimensScope { id: ad; target: win }

    Rectangle {
        anchors.centerIn: parent
        width: ad.asdp(280); height: ad.asdp(180)
        radius: ad.sdp(12)
        color: "#1d4ed8"
        Column {
            anchors.fill: parent; anchors.margins: ad.sdp(16); spacing: ad.sdp(8)
            Text { text: "AppDimens for QML"; color: "white"; font.pixelSize: ad.assp(20); font.bold: true }
            Text { text: ad.width.toFixed(0) + " × " + ad.height.toFixed(0) + " · dpr " + ad.density
                   color: "white"; font.pixelSize: ad.ssp(14) }
        }
    }
}
