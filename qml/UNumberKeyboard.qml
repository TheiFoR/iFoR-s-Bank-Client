import QtQuick
import QtQuick.Layouts

GridLayout {
    property int buttonSize: 50
    property int fontSize: 25
    property var value: ""
    property int maxLenght: 4

    id: control

    rows: 4
    columns: 3

    signal finished(string text)

    FontLoader {
        id: robotoRegular
        source: "qrc:/assets/fonts/Roboto/Roboto-Regular.ttf"
    }

    Repeater{
        model: 12
        UButton{
            backgroundColor: index === 11
                             ? "transparent"
                             : "#262626"
            backgroundPressedColor: index === 11
                                    ? backgroundColor
                                    : "#303030"

            enabled: (index !== 9)
            opacity: enabled ? 1 : 0

            text: index === 10
                  ? 0
                  : index == 11
                    ? ""
                    : index + 1

            icon.source: index !== 11
                         ? ""
                         : "qrc:/assets/images/icons/left_arrow.svg"
            icon.color: "#303030"
            iconPressedColor: "#404040"

            font.family: robotoRegular.font.family
            font.styleName: robotoRegular.font.styleName
            font.pixelSize: control.fontSize

            Layout.alignment: Qt.AlignCenter
            Layout.minimumWidth: control.buttonSize
            Layout.minimumHeight: control.buttonSize
            Layout.maximumWidth: control.buttonSize
            Layout.maximumHeight: control.buttonSize

            onClicked:{
                if(value.length == maxLenght){
                    finished(value)
                }
                else{
                    if(index == 11){
                        value = value.slice(0, -1)
                    }
                    else{
                        value = value + text
                    }
                }
            }
        }
    }
}
