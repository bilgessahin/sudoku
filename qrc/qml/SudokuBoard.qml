import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import Style 1.0


ColumnLayout {
    anchors.centerIn: parent
    property alias gridView: sudokuGrid.gridView


    Row {
        width: 450
        height: 400
        Repeater {
            model: 9
            delegate: Text {
                text: index + 1
                font.pixelSize: 24
                width: sudokuGrid.width / 9
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }


    Rectangle {
        id: sudokuGrid
        width: 450
        height: 400
        color: Style.boardFirstColor

        property alias gridView: gridView

        Canvas {
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d");
                ctx.clearRect(0, 0, width, height);
                ctx.fillStyle = Style.boardSecondColor
                for (var i = 0; i < 9; i += 2) {
                    ctx.fillRect(0, i * (height / 9), width, height / 9);
                }

                ctx.strokeStyle = Style.borderColor;
                ctx.lineWidth = 1;
                ctx.strokeRect(0, 0, width, height);
            }
        }

        GridView {
            id: gridView
            anchors.fill: parent
            model: sudokuModel
            cellWidth: sudokuGrid.width / 9
            cellHeight: sudokuGrid.height / 9
            delegate: Rectangle {
                id: delegateBackground
                width: sudokuGrid.width / 9
                height: sudokuGrid.height / 9
                color: Style.transparent
                TextField {
                    property bool isCorrect: true
                    id: myTextField
                    text: model.number === 0 ? "" : model.number
                    anchors.fill: parent
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    font.pixelSize: 24
                    color: Style.textColor
                    readOnly: model.fixed
                    inputMethodHints: Qt.ImhDigitsOnly

                    validator: RegExpValidator { regExp: /^[1-9]$/ }

                    onActiveFocusChanged: {

                        if(!isFineshed){

                            if (activeFocus && !model.fixed) {
                                selectAll()
                                background.color = Style.selectedCellColor
                            }
                            if(!activeFocus && !model.fixed){
                                if(isCorrect)
                                    background.color = Style.transparent
                                else
                                    background.color = Style.wrongColor
                            }

                            functions.calculateAndControl(index);
                        }

                    }
                    background: Rectangle{
                        id: background
                        color: Style.transparent;
                    }

                    onEditingFinished: {

                        userInput = true;

                        var modelIndex = sudokuModel.index(index, 0);
                        sudokuModel.setData(modelIndex, text, sudokuModel.numberRole());

                        if(!isFineshed){
                            functions.calculateAndControl(index);
                        }

                        if (functions.checkBoardComplete()) {
                            isFineshed = true;
                            functions.changeAllCellsColor(Style.finishedColor);
                        }

                    }


                    onTextChanged: {

                        if (userInput){
                            if (text.length > 0) {
                                var row = Math.floor(index / 9);
                                var col = index % 9;
                                var num = parseInt(text);
                                if (sudokuModel.isInRow(row, num) || sudokuModel.isInColumn(col, num)) {
                                    background.color = Style.wrongColor;
                                    myTextField.color = Style.selectedCellColor;
                                    isCorrect = false;
                                } else {
                                    background.color = Style.transparent;
                                    myTextField.color = Style.textColor;
                                    isCorrect = true;
                                }
                            } else {
                                background.color = Style.transparent;
                                myTextField.color = Style.textColor;
                                isCorrect = true;
                                var modelIndex = sudokuModel.index(index, 0);
                                sudokuModel.setData(modelIndex, 0, sudokuModel.numberRole());

                            }
                        }
                    }
                }

            }
        }
    }

    Button {
        text: "Generate!"
        Layout.alignment: Qt.AlignHCenter
        onClicked: {
            userInput = false;
            sudokuController.resetBoard()
            functions.resetColor();
            functions.controlBeginningColor();
            isFineshed = false;
        }
    }
}


