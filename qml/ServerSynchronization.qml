import QtQuick
import QtQuick.Controls

Rectangle {
    id: root

    color: "#191919"

    BusyIndicator {
        anchors.centerIn: parent
        running: true
    }
}
