#include "MainWindow.h"
//#include "Updates.h"
#include <QApplication>

//Updates* updates;


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
//  updates = new Updates;
  MainWindow w;
  w.show();

  return a.exec();
}
