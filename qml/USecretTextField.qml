import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic
import QtQuick.Effects

UTextField{
    property string secretShowIcon: "qrc:/assets/images/icons/visibility.svg"
    property string secretHideIcon: "qrc:/assets/images/icons/visibility_off.svg"

    property bool show: false

    id: control

    passwordCharacter: '*'

    echoMode: control.show
                ? TextInput.Normal
                : TextInput.Password

    rightPadding: 20

    Image{
        id: icon
        visible: false
        source: control.show
                ? control.secretShowIcon
                : control.secretHideIcon
        antialiasing: true
        fillMode: Image.PreserveAspectFit
        width: control.rightPadding
        anchors{
            right: control.right
            bottom: control.bottom
            top: control.top
            margins: 5
        }
    }

    MultiEffect{
        source: icon
        anchors.fill: icon
        colorizationColor: control.color
        colorization: 1
    }

    MouseArea{
        anchors.fill: icon
        onPressed:{
            control.show = !control.show
        }
    }
}
