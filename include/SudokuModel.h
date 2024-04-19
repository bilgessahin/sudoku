#ifndef SUDOKUMODEL_H
#define SUDOKUMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QRandomGenerator>

class SudokuModel : public QAbstractListModel
{
  Q_OBJECT
public:
  enum
  {
    NumberRole = Qt::UserRole + 1,
    FixedRole
  };

  explicit SudokuModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

  Q_INVOKABLE bool isInColumn(int col, int number) const;
  Q_INVOKABLE bool isInRow(int row, int number) const;
  Q_INVOKABLE void generateNumbers();

  Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
  Q_INVOKABLE int numberRole() const;

  Q_INVOKABLE bool isRowComplete(int row) const;
  Q_INVOKABLE bool isColumnComplete(int col) const;

private:
  bool isInBox(int startRow, int startCol, int number) const;
  bool isSafe(int row, int col, int number) const;
  void removeCells(double percentage);

  void clearBoard();
  bool fillBoard(int index);

private:
  QVector<int> numbers;
  QVector<bool> fixed;
};

#endif // SUDOKUMODEL_H
