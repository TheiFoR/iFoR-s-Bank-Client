import QtQuick
import QtQuick.Layouts

Rectangle {
    id: root

    color: "#191919"

    FontLoader {
        id: robotoRegular
        source: "qrc:/assets/fonts/Roboto/Roboto-Regular.ttf"
    }
    FontLoader {
        id: robotoBlack
        source: "qrc:/assets/fonts/Roboto/Roboto-Black.ttf"
    }


    ColumnLayout{
        anchors.fill: parent
        anchors.margins: 30

        Text{
            Layout.fillWidth: true
            Layout.preferredHeight: 1
            Layout.alignment: Qt.AlignTop

            text: qsTr("Log in")
            color: "#ffffff"
            font.family: robotoBlack.font.family
            font.styleName: robotoBlack.font.styleName
            font.pixelSize: 40
        }
        Column{
            Layout.fillWidth: true
            Layout.preferredHeight: 1

            spacing: 10
            UTextField{
                id: phoneNumber

                placeholderText: qsTr("Phone number")
                font.family: robotoRegular.font.family
                font.styleName: robotoRegular.font.styleName
                font.pixelSize: 17
                icon: "qrc:/assets/images/icons/phone.svg"
                anchors{
                    left: parent.left
                    right: parent.right
                }
            }
            USecretTextField{
                id: pinCode

                placeholderText: qsTr("Pin code")
                font.family: robotoRegular.font.family
                font.styleName: robotoRegular.font.styleName
                font.pixelSize: 17
                icon: "qrc:/assets/images/icons/lock.svg"
                anchors{
                    left: parent.left
                    right: parent.right
                }
            }
            Text{
                text: core.serverMessage
                color: core.serverMessageColor
                font.family: robotoRegular.font.family
                font.styleName: robotoRegular.font.styleName
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                anchors{
                    left: parent.left
                    right: parent.right
                }
            }
        }
        Column{
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredHeight: 2

            spacing: 10
            UButton{
                width: root.width / 2
                font.family: robotoBlack.font.family
                font.styleName: robotoBlack.font.styleName
                font.pixelSize: 30
                text: qsTr("Log in")

                onClicked:{
                    core.sendLogInRequest(phoneNumber.text, pinCode.text)
                }
            }
            Row{
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 0
                Text{
                    id: signUpText
                    text: qsTr("First time here?")
                    font.family: robotoRegular.font.family
                    font.styleName: robotoRegular.font.styleName
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    color: "white"
                }
                UButton{
                    font.family: robotoRegular.font.family
                    font.styleName: robotoRegular.font.styleName
                    font.pixelSize: 12
                    height: signUpText.height
                    backgroundColor: "transparent"
                    textColor: "#859da9"
                    textPressedColor: "#c8e2f2"
                    text: qsTr("Sign up.")

                    onClicked:{
                        core.userRegistration = 1 // set registration page
                    }
                }
            }
        }
    }
}
