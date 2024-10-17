import QtQuick
import QtQuick.Effects
import QtQuick.Controls
import QtQuick.Controls.Basic

TextField {
    id: control

    property string icon: ""

    property string focusedColor: "#a38756"
    property string color: "#262626"

    placeholderTextColor: control.color

    leftPadding: 30

    background: Item{
        width: control.width
        height: control.height

        Rectangle{
            id: bottomLine
            anchors{
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }
            color: control.focus
                    ? control.focusedColor
                    : control.color
            height: 1
        }

        Image{
            id: icon
            visible: false
            source: control.icon
            antialiasing: true
            fillMode: Image.PreserveAspectFit
            width: control.leftPadding - anchors.margins * 2
            anchors{
                left: parent.left
                bottom: parent.bottom
                top: parent.top
                margins: 5
            }
        }

        MultiEffect{
            visible: control.icon !== ""
            source: icon
            anchors.fill: icon
            colorizationColor: bottomLine.color
            colorization: 1
        }
    }
}
