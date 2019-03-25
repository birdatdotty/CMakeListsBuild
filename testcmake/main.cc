#include "Widget/Widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
//  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QApplication app(argc, argv);
  Widget* w = new Widget;
  w->show();

  return app.exec();
}
