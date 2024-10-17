import QtQuick
import QtQuick.Layouts

Item {
    id: root

    property int currentIndex: 2
    property int duration: 1000

    Layout.fillWidth: true
    Layout.fillHeight: true

    width: 100
    height: 100

    onCurrentIndexChanged:{

    }

    Component.onCompleted:{
        for(let i = 0; i < root.children.length; ++i){
            root.children[i].visible = (i === 0)
        }
        console.warn(width, height)
    }
}
