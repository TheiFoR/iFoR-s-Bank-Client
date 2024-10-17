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
                client.userRegistrationStep = 0 // set log in page
            }
        }
        ColumnLayout{
            width: parent.width
            height: parent.height - backButton.height
            Row{
                Layout.fillWidth: true
                Layout.preferredHeight: 1
                Layout.alignment: Qt.AlignTop
                Layout.minimumHeight: registrationLabel.height

                Text{
                    id: registrationLabel
                    width: parent.width / 2

                    text: qsTr("Link Telegram")
                    color: "#ffffff"
                    font.family: robotoBlack.font.family
                    font.styleName: robotoBlack.font.styleName
                    font.pixelSize: 40
                    wrapMode: Text.WordWrap
                }
                Item{
                    id: stepsLabel
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
                Layout.minimumHeight: pinView.height + numberKeyboard.height + spacing /*info.height + spacing */
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredHeight: 1

                spacing: 50
                // Text{
                //     id: info
                //     text: qsTr("Enter the code")
                //     font.family: robotoBlack.font.family
                //     font.styleName: robotoBlack.font.styleName
                //     font.pixelSize: 30
                //     horizontalAlignment: Text.AlignHCenter
                //     wrapMode: Text.WordWrap
                //     anchors{
                //         left: parent.left
                //         right: parent.right
                //     }
                //     color: "#262626"
                // }
                UPinView{
                    id: pinView
                    anchors{
                        left: parent.left
                        right: parent.right
                    }
                    value: numberKeyboard.value
                }
                UNumberKeyboard{
                    id: numberKeyboard
                    anchors{
                        left: parent.left
                        right: parent.right
                    }
                    rowSpacing: 20
                }
            }
            Row{
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredHeight: 1
                spacing: 0
                Text{
                    id: signUpText
                    text: qsTr("Didn't get the code?")
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
                    text: qsTr("Send again.")

                    onClicked:{
                        client.userRegistration = 0 // set log in page
                    }
                }
            }
        }
    }
}
