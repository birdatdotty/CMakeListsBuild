#include "Widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
  : QWidget(parent),
    ok("OK")
{
  qInfo() << "Widget::Widget";
  mainLayout.addWidget(&ok);
  setLayout(&mainLayout);

  connect(&ok, &QPushButton::released, [=](){
		  delete this;
		  });
}
