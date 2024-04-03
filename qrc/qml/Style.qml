pragma Singleton
import QtQuick 2.0
import QtQml 2.0

QtObject {

    // numeric properties
    property int rotationAngle: 90
    property int applicationWidth: 480
    property int applicationHeight: 640
    property real objectScale: 0.9


    //colors
    property color transparent: "transparent"
    property color textColor: "midnightblue"
    property color appBackgroundColor: "white"
    property color abtCircleColor: "red"
    property color emvCircleColor: "blue"
    property color madtCircleColor: "yellow"
    property color devManagerCircleColor: "green"

    //fonts
    property string applicationFont: "akkuratRegular"
    property string applicationBoldFont: "akkuratBold"

    //fonts size
    property int applicationFontSize: 14

}
