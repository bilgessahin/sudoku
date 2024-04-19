#ifndef SUDOKUCONTROLLER_H
#define SUDOKUCONTROLLER_H

#include "SudokuModel.h"
#include <QObject>

class SudokuController : public QObject
{
  Q_OBJECT
public:
  explicit SudokuController(QObject *parent = nullptr);

  Q_INVOKABLE void setModel(SudokuModel *model);
  Q_INVOKABLE void resetBoard();
  Q_INVOKABLE void updateCell(int index, int value);

private:
  SudokuModel *model;
};

#endif // SUDOKUCONTROLLER_H
