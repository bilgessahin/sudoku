#include "SudokuController.h"
#include "SudokuModel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  qmlRegisterType<SudokuModel>("SudokuModel", 1, 0, "SudokuModel");
  qmlRegisterType<SudokuController>("SudokuController", 1, 0, "SudokuController");

  qmlRegisterSingletonType(QStringLiteral("qrc:/qml/Style.qml"), "Style", 1, 0, "Style");

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
