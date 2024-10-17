import QtQuick
import QtQuick.Layouts

Window {
    width: 393
    height: 884
    visible: true
    title: qsTr("iFoR's Bank")

    StackLayout{
        anchors.fill: parent
        currentIndex: (core.serverConnected ? 1 : 0)

        Preview{}

        StackLayout{
            currentIndex: core.userAuthorization

            Authorization{}
            ServerSynchronization{}
            App{}
        }
    }
}
