#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

#include "Config.h"


//class CMakeListsBuild;
#include "CMakeListsBuild/CMakeListsBuild.h"
//class Components;
#include "Components/Components.h"
//class ComponentsFiles;
#include "ComponentsFiles/ComponentsFiles.h"
class ProBuild;
#include "CheckMode/CheckMode.h"
class SubPrj;
class ExtendedLib;

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
  CMakeListsBuild *cMakeListsBuild;
  ProBuild *proBuild;
  Components *componentsWdget;
  ComponentsFiles *componentsFiles;
  SubPrj *subPrj;
  CheckMode *checkMode;
  ExtendedLib *extendedLib;
  QLabel *lPrjPath, *lNamePrj;
  QLineEdit *ePrjPath, *eNamePrj;
  QPushButton *btnPrjPath;

  Config *config;
};

#endif // WIDGET_H
