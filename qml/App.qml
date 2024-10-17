import QtQuick
import QtQuick.Layouts

Rectangle {
    color: "#191919"

    ColumnLayout{
        anchors{
            left: parent.left
            top: parent.top
            right: parent.right
            bottom: navigationBar.top
        }

        RowLayout{
            Layout.preferredHeight: 140
            Rectangle{

                radius: Layout.preferredHeight / 2
            }
        }
    }

    NavBar{
        id: navigationBar
        height: 60
    }
}
