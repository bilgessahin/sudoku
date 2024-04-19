import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import SudokuController 1.0
import SudokuModel 1.0
import Style 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    width: Style.applicationWidth
    height: Style.applicationHeight
    title: "Sudoku Game"
    flags: Qt.Window | Qt.WindowTitleHint | Qt.WindowCloseButtonHint

    property bool userInput: false
    property bool isFineshed: false
    property alias gridView: board.gridView


    SudokuModel {
        id: sudokuModel
    }

    SudokuController {
        id: sudokuController
    }

    Functions{
        id: functions
    }

    Rectangle {
        width: 600
        height: 500
        color: Style.transparent
        anchors.centerIn: parent
        border.color: Style.borderColor
        radius: Style.radius

        RowLayout{
            anchors.centerIn: parent
            spacing: 50
            Column {
                Repeater {
                    model: 9
                    delegate: Text {
                        text: index + 1
                        font.pixelSize: 24
                        height: 400 / 9
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }

            SudokuBoard{
                id: board
            }
        }
    }
    Component.onCompleted: {
        sudokuController.setModel(sudokuModel);
        sudokuController.resetBoard();
        userInput = true;
        functions.controlBeginningColor();
    }
}



