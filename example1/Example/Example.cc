#include "Example.h"

#include "Button1/Button1.h"
#include "Button2/Button2.h"

Example::Example(QWidget *parent)
  : QWidget(parent)
{
  button1 = new Button1();
  button2 = new Button2();

  mainLayout.addWidget(button1);
  mainLayout.addWidget(button2);

  setLayout(&mainLayout);
}

Example::~Example()
{

}
