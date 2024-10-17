import QtQuick

Row{
    property int maxLength: 4
    property string value: "ss"

    property color color: "#262626"
    property color backgroundColor: "#191919"

    id: control

    height: 10

    Repeater{
        id: repeater
        model: control.maxLength
        delegate: Item{
            width: control.width / control.maxLength
            height: control.height
            Rectangle{
                anchors.centerIn: parent
                height: parent.height
                width: parent.height
                radius: height / 2
                color: control.value.length > index
                        ? control.color
                        : control.backgroundColor
                border{
                    width: 1
                    color: control.color
                }
                Behavior on color{
                    ColorAnimation{
                        duration: 250
                    }
                }
            }
        }
    }

    SequentialAnimation{
        ParallelAnimation{}
    }

    onValueChanged:{
        if(value.length === maxLength){
        }
    }
}
