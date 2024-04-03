import QtQuick 2.12
import QtQuick.Window 2.12
import Style 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle{
    width: 50
    height: 50
    color: Style.abtCircleColor
    }
}
