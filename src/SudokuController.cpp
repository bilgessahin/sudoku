#include "SudokuController.h"

SudokuController::SudokuController(QObject *parent) : QObject(parent), model(nullptr)
{
}

void SudokuController::setModel(SudokuModel *model)
{

  if (this->model != model)
  {
    this->model = model;
  }
}

void SudokuController::resetBoard()
{
  if (model)
  {
    model->generateNumbers();
  }
}

void SudokuController::updateCell(int index, int value)
{
  if (model)
  {
    model->setData(model->index(index, 0), value, SudokuModel::NumberRole);
  }
}
