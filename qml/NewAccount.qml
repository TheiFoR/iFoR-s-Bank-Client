import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

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




    Column{
        anchors.fill: parent
        anchors.margins: 30
        spacing: 10

        UButton{
            id: backButton
            height: 25
            width: 25
            display: AbstractButton.IconOnly
            backgroundColor: "transparent"
            icon{
                source: "qrc:/assets/images/icons/left_arrow.svg"
                color: "white"
            }

            onClicked:{
                core.userRegistration = 0 // set log in page
            }
        }
        ColumnLayout{
            width: parent.width
            height: parent.height - backButton.height
            Row{
                Layout.fillWidth: true
                Layout.preferredHeight: 1
                Layout.alignment: Qt.AlignTop
                Text{
                    id: registrationLabel
                    width: parent.width / 2

                    text: qsTr("New Account")
                    color: "#ffffff"
                    font.family: robotoBlack.font.family
                    font.styleName: robotoBlack.font.styleName
                    font.pixelSize: 40
                    wrapMode: Text.WordWrap
                }
                Item{
                    width: parent.width / 2
                    height: registrationLabel.height
                    Column{
                        anchors{
                            right: parent.right
                            bottom: parent.bottom
                        }
                        Row{
                            Text{
                                id: ccc
                                font.family: robotoBlack.font.family
                                font.styleName: robotoBlack.font.styleName
                                font.pixelSize: 27
                                text: core.userRegistrationStep + 1
                                color: "white"
                            }
                            Text{
                                font.family: robotoBlack.font.family
                                font.styleName: robotoBlack.font.styleName
                                font.pixelSize: 15
                                text: "/2"
                                color: "white"
                                verticalAlignment: Text.AlignBottom
                                anchors{
                                    bottom: ccc.bottom
                                    bottomMargin: ccc.font.pixelSize / 7.2
                                }
                            }
                        }
                        Row{
                            Text{
                                font.family: robotoBlack.font.family
                                font.styleName: robotoBlack.font.styleName
                                font.pixelSize: 15
                                text: "steps"
                                color: "white"
                            }
                        }
                    }
                }
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
                    text: qsTr("Next")

                    onClicked:{
                        core.sendSignUpRequest(phoneNumber.text, pinCode.text)
                    }
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 0
                    Text{
                        id: signUpText
                        text: qsTr("Not the first time here?")
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
                        text: qsTr("Log in.")

                        onClicked:{
                            core.userRegistration = 0 // set log in page
                        }
                    }
                }
            }
        }
    }
}
