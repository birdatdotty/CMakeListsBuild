#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QString defaultPath;
  if (argc > 1)
    defaultPath = argv[1];

  QApplication a(argc, argv);
  MainWindow w(defaultPath);
  w.show();

  return a.exec();
}
