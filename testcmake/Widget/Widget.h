#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

class Widget : public QWidget
{
  Q_OBJECT
public:
  explicit Widget(QWidget *parent = nullptr);

signals:

public slots:

private:
  QGridLayout mainLayout;
  QPushButton ok;

};

#endif // WIDGET_H
