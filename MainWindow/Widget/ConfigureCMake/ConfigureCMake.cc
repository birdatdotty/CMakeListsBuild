#include "ConfigureCMake.h"

#include "CMakeListsBuild/CMakeListsBuild.h"
#include "ProBuild/ProBuild.h"
#include "Components/Components.h"
#include "ComponentsFiles/ComponentsFiles.h"
#include "CheckMode/CheckMode.h"
#include "SubPrj/SubPrj.h"
#include "ExtendedLib/ExtendedLib.h"
//#include "TreePrj/TreePrj.h"


ConfigureCMake::ConfigureCMake(Config *config, QWidget *parent)
  : QWidget(parent)
{
  lPrjPath = new QLabel("Путь к проекту:");
  ePrjPath = new QLineEdit(config->getPrjPath());
  btnPrjPath = new QPushButton("...");

  lNamePrj = new QLabel("Имя проекта:");
  eNamePrj = new QLineEdit();

  checkMode = new CheckMode;

  cMakeListsBuild = new CMakeListsBuild(this);

  componentsWdget = new Components(this);
  componentsFiles = new ComponentsFiles(this);
  subPrj = new SubPrj(this);

  proBuild = new ProBuild(this);

  extendedLib = new ExtendedLib();

  mainLayout.addWidget(lPrjPath,0,0);
  mainLayout.addWidget(ePrjPath, 0, 1, 1, 2);
//  mainLayout.addWidget(btnPrjPath,0,2);

  mainLayout.addWidget(lNamePrj, 1, 0);
  mainLayout.addWidget(eNamePrj, 1, 1, 1, 2);

  mainLayout.addWidget(checkMode, 2, 0, 1, 3);

  mainLayout.addWidget(componentsWdget, 3, 0);
  mainLayout.addWidget(componentsFiles, 3, 1);
  mainLayout.addWidget(subPrj, 3, 2);
  mainLayout.addWidget(extendedLib,4,0,1,3);
  mainLayout.addWidget(cMakeListsBuild, 5, 0);
  mainLayout.addWidget(proBuild, 5, 1, 1, 2);

  connect(ePrjPath, &QLineEdit::textChanged, config, &Config::setPrjPath);
  connect(eNamePrj, &QLineEdit::textChanged, config, &Config::setPrjName);

  setLayout(&mainLayout);
}

void ConfigureCMake::update(QString path, QJsonObject obj)
{
  if (curPath == path)
    return;

  curPath = path;
  ePrjPath->setText(path);
  eNamePrj->setText(obj["name"].toString());
  componentsWdget->update(obj["Qt"].toArray());
  componentsFiles->update(obj["sources"].toArray(),
                          obj["headers"].toArray());
  subPrj->update(obj["dirs"].toArray());
  extendedLib->update(obj["pc"].toArray());
  checkMode->updateMode(obj["mode"].toString("StaticLib"));
}
