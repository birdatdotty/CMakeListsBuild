#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "Config.h"


class CMakeListsBuild;
class Components;
class ComponentsFiles;
class ProBuild;
class CheckMode;
class SubPrj;
class ExtendedLib;
class TreePrj;

class ConfigureCMake;
class NamePrj;

class Widget : public QWidget
{
  Q_OBJECT
public:
  explicit Widget(Config *config, QWidget *parent = nullptr);
  ~Widget();

signals:

public slots:

private:

  QGridLayout mainLayout;
  NamePrj* namePrj;
  TreePrj* treePrj;
  SubPrj *subPrj;
  CheckMode *checkMode;
  ExtendedLib *extendedLib;
  QLabel *lPrjPath, *lNamePrj;
  QLineEdit *ePrjPath, *eNamePrj;
  QPushButton *btnPrjPath;
  ConfigureCMake* configureCMake;

  Config *config;
};

#endif // WIDGET_H
