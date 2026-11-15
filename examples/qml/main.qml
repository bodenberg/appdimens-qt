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
        width: 280 * ad.asdp; height: 180 * ad.asdp
        radius: 12 * ad.sdp
        color: "#1d4ed8"
        Column {
            anchors.fill: parent; anchors.margins: 16 * ad.sdp; spacing: 8 * ad.sdp
            Text { text: "AppDimens for QML"; color: "white"; font.pixelSize: 20 * ad.assp; font.bold: true }
            Text { text: ad.width.toFixed(0) + " × " + ad.height.toFixed(0) + " · dpr " + ad.density
                   color: "white"; font.pixelSize: 14 * ad.ssp }
        }
    }
}
