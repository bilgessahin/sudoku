pragma Singleton
import QtQuick 2.0
import QtQml 2.0

QtObject {

    // numeric properties
    property int applicationWidth: 700
    property int applicationHeight: 600
    property int radius: 80


    //colors
    property color transparent: "transparent"
    property color textColor: "black"
    property color borderColor: "black"
    property color selectedCellColor: "white"
    property color wrongColor: "#d80073"
    property color completedColor: "gray"
    property color finishedColor: "green"

    property color boardFirstColor: "#dae8fc"
    property color boardSecondColor: "#ffe6cc"

    //fonts
    property string applicationFont: "akkuratRegular"
    property string applicationBoldFont: "akkuratBold"

    //fonts size
    property int applicationFontSize: 14

}
