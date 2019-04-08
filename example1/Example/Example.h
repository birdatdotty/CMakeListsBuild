#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QWidget>
#include <QVBoxLayout>
class Button1;
class Button2;

class Example : public QWidget
{
  Q_OBJECT

public:
  Example(QWidget *parent = nullptr);
  ~Example();

private:
  QVBoxLayout mainLayout;
  Button1 *button1;
  Button2 *button2;
};

#endif // EXAMPLE_H
