import QtQuick 2.0
import Style 1.0

QtObject {

    function changeRowColor(row, color) {
        for (var i = 0; i < 9; i++) {
            var idx = row * 9 + i;
            var delegate = gridView.contentItem.children[idx];
            delegate.children[0].background.color = color;
        }
    }

    function changeColumnColor(col, color) {
        for (var i = 0; i < 9; i++) {
            var idx = i * 9 + col;
            var delegate = gridView.contentItem.children[idx];
            delegate.children[0].background.color = color;
        }
    }

    function changeAllCellsColor(color) {
        for (var i = 0; i < 81; i++) {
            var delegate = gridView.contentItem.children[i];
            delegate.children[0].background.color = color;
            delegate.children[0].color = Style.textColor;
        }
    }

    function resetColor(){
        changeAllCellsColor(Style.transparent)
    }

    function checkBoardComplete() {
        for (var row = 0; row < 9; row++) {
            if (!sudokuModel.isRowComplete(row)) {
                return false;
            }
        }
        for (var col = 0; col < 9; col++) {
            if (!sudokuModel.isColumnComplete(col)) {
                return false;
            }
        }
        return true;
    }

    function controlBeginningColor(){

        for(var i = 0; i < 9; i++){

            if (sudokuModel.isRowComplete(i)){
                changeRowColor(i, Style.completedColor);
            }

            if(sudokuModel.isColumnComplete(i)){
                changeColumnColor(i, Style.completedColor);
            }
        }
    }

    function calculateAndControl(index){
        var row = Math.floor(index / 9);
        var col = index % 9;

        if (sudokuModel.isRowComplete(row)){
            functions.changeRowColor(row, Style.completedColor);
        }

        if(sudokuModel.isColumnComplete(col)){
            functions.changeColumnColor(col, Style.completedColor);
        }
    }
}

