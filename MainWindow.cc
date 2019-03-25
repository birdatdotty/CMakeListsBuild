#include "MainWindow.h"

#include "Widget.h"
Config* config;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
//  cMakeListsBuild = new CMakeListsBuild();
  config = new Config;
  widget = new Widget(config);
  setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
  delete widget;
}
