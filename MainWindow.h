#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "Config.h"

class CMakeListsBuild;
class Widget;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  CMakeListsBuild *cMakeListsBuild;
  Widget* widget;
};

#endif // MAINWINDOW_H
