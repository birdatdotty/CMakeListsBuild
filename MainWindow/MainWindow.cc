#include "MainWindow.h"

#include "Widget/Widget.h"
Config* config;

MainWindow::MainWindow(QString str)
{
//  cMakeListsBuild = new CMakeListsBuild();
  config = new Config;
  widget = new Widget(config, str, this);
  setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
  delete widget;
}
