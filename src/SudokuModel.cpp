#include "SudokuModel.h"
#include <QDateTime>
#include <QSet>

SudokuModel::SudokuModel(QObject *parent) : QAbstractListModel(parent), numbers(81, 0), fixed(81, false)
{
  generateNumbers();
}

int SudokuModel::rowCount(const QModelIndex &parent) const
{
  return 81;
}

QVariant SudokuModel::data(const QModelIndex &index, int role) const
{
  int row = index.row();
  if (role == NumberRole)
    return numbers[row];
  if (role == FixedRole)
    return fixed[row];
  return QVariant();
}

QHash<int, QByteArray> SudokuModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[NumberRole] = "number";
  roles[FixedRole] = "fixed";
  return roles;
}

void SudokuModel::generateNumbers()
{
  clearBoard();
  fillBoard(0);
  removeCells(40);
  emit dataChanged(index(0, 0), index(80, 0), {NumberRole, FixedRole});
}

void SudokuModel::clearBoard()
{
  for (int i = 0; i < 81; ++i)
  {
    numbers[i] = 0;
    fixed[i] = false;
  }
}

void SudokuModel::removeCells(double percentage)
{
  int totalCells = 81;
  int cellsToRemove = static_cast<int>(totalCells * percentage / 100.0);
  QRandomGenerator *generator = QRandomGenerator::global();

  while (cellsToRemove > 0)
  {
    int cellIndex = generator->bounded(0, totalCells);
    if (numbers[cellIndex] != 0)
    {
      numbers[cellIndex] = 0;
      fixed[cellIndex] = false;
      cellsToRemove--;
    }
  }
}

bool SudokuModel::fillBoard(int index)
{
  if (index >= 81)
  {
    return true;
  }

  int row = index / 9;
  int col = index % 9;

  QVector<int> availableNumbers{1, 2, 3, 4, 5, 6, 7, 8, 9};
  QRandomGenerator *generator = QRandomGenerator::global();
  std::shuffle(availableNumbers.begin(), availableNumbers.end(), *generator);

  for (int num : availableNumbers)
  {
    if (isSafe(row, col, num))
    {
      numbers[index] = num;
      fixed[index] = true;

      if (fillBoard(index + 1))
      {
        return true;
      }

      numbers[index] = 0;
      fixed[index] = false;
    }
  }

  return false;
}

bool SudokuModel::isSafe(int row, int col, int number) const
{
  int boxStartRow = row - row % 3;
  int boxStartCol = col - col % 3;

  return !isInRow(row, number) && !isInColumn(col, number) && !isInBox(boxStartRow, boxStartCol, number);
}

bool SudokuModel::isInRow(int row, int number) const
{
  for (int col = 0; col < 9; ++col)
  {
    if (numbers[row * 9 + col] == number)
    {
      return true;
    }
  }
  return false;
}

bool SudokuModel::isInBox(int startRow, int startCol, int number) const
{
  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      if (numbers[(startRow + i) * 9 + (startCol + j)] == number)
      {
        return true;
      }
    }
  }
  return false;
}

bool SudokuModel::isInColumn(int col, int number) const
{
  for (int row = 0; row < 9; ++row)
  {
    if (numbers[row * 9 + col] == number)
    {
      return true;
    }
  }
  return false;
}

bool SudokuModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (index.row() < 0 || index.row() >= numbers.size() || role != NumberRole)
    return false;
  numbers[index.row()] = value.toInt();
  emit dataChanged(index, index, {role});
  return true;
}

int SudokuModel::numberRole() const
{
  return NumberRole;
}

bool SudokuModel::isRowComplete(int row) const
{

  QSet<int> existNum;
  for (int col = 0; col < 9; ++col)
  {
    int value = numbers[row * 9 + col];
    if (value == 0 || existNum.contains(value))
      return false;
    existNum.insert(value);
  }
  return existNum.size() == 9;
}

bool SudokuModel::isColumnComplete(int col) const
{

  QSet<int> existNum;
  for (int row = 0; row < 9; ++row)
  {
    int value = numbers[row * 9 + col];
    if (value == 0 || existNum.contains(value))
      return false;
    existNum.insert(value);
  }
  return existNum.size() == 9;
}
