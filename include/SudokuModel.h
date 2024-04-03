#ifndef SUDOKUMODEL_H
#define SUDOKUMODEL_H

#include <QObject>
#include <QVector>

class SudokuModel : public QObject
{
  Q_OBJECT
public:
  explicit SudokuModel(QObject *parent = nullptr);

  Q_INVOKABLE void generateSudoku();
  Q_INVOKABLE QVector<QVector<int>> getSudokuGrid() const;

signals:
  void sudokuGenerated();

private:
  QVector<QVector<int>> m_sudokuGrid;

  bool isValidPlacement(int row, int col, int num);
  bool solveSudoku();
};

#endif // SUDOKUMODEL_H
