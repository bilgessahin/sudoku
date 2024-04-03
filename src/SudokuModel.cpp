#include <QDebug>
#include <SudokuModel.h>

SudokuModel::SudokuModel(QObject *parent) : QObject(parent)
{
  // Sudoku modelini başlat
  m_sudokuGrid = QVector<QVector<int>>(9, QVector<int>(9, 0));
}

void SudokuModel::generateSudoku()
{
  // Sudoku tablosunu oluştur
  solveSudoku();

  // Oluşturulan Sudoku tablosunu yayınla
  emit sudokuGenerated();
}

QVector<QVector<int>> SudokuModel::getSudokuGrid() const
{
  return m_sudokuGrid;
}

bool SudokuModel::isValidPlacement(int row, int col, int num)
{
  // Satırı kontrol et
  for (int i = 0; i < 9; ++i)
    if (m_sudokuGrid[row][i] == num)
      return false;

  // Sütunu kontrol et
  for (int i = 0; i < 9; ++i)
    if (m_sudokuGrid[i][col] == num)
      return false;

  // Küçük 3x3 kutuyu kontrol et
  int startRow = row - row % 3;
  int startCol = col - col % 3;
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      if (m_sudokuGrid[i + startRow][j + startCol] == num)
        return false;

  return true;
}

bool SudokuModel::solveSudoku()
{
  for (int row = 0; row < 9; ++row)
  {
    for (int col = 0; col < 9; ++col)
    {
      if (m_sudokuGrid[row][col] == 0)
      {
        for (int num = 1; num <= 9; ++num)
        {
          if (isValidPlacement(row, col, num))
          {
            m_sudokuGrid[row][col] = num;
            if (solveSudoku())
              return true;
            m_sudokuGrid[row][col] = 0;
          }
        }
        return false;
      }
    }
  }
  return true;
}
