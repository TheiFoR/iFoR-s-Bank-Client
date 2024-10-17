import QtQuick

Rectangle{
    id: root

    color: "black"

    Image{
        id: previewLogo
        anchors.fill: parent
        source: "qrc:/assets/images/logo/preview.png"
        sourceSize.width: parent.width
        fillMode : Image.PreserveAspectFit
    }
}
