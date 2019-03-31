#include "Widget.h"

#include "CMakeListsBuild/CMakeListsBuild.h"
#include "ProBuild/ProBuild.h"
#include "Components/Components.h"
#include "ComponentsFiles/ComponentsFiles.h"
#include "CheckMode/CheckMode.h"
#include "SubPrj/SubPrj.h"
#include "ExtendedLib/ExtendedLib.h"
#include "TreePrj/TreePrj.h"
#include "NamePrj/NamePrj.h"

#include "ConfigureCMake.h"


Widget::Widget(Config *config, QWidget *parent)
  : QWidget(parent),
    config (config)
{
  config->setPrjPath("");




//  QJsonObject obj;
//  obj["name"] = "qwe";
//  QJsonArray sources;
//  sources.append("main.cc");
//  sources.append("main1.cc");
//  sources.append("main2.cc");
//  sources.append("main3.cc");
//  obj["sources"] = sources;
//  QJsonArray headers;
//  headers.append("main.h");
//  headers.append("main.h");
//  headers.append("main.h");
//  obj["headers"] = headers;
//  QJsonArray dirs;
//  dirs.append("Widget");
//  obj["dirs"] = dirs;
//  QJsonArray qt;
//  qt.append("Widgets");
//  qt.append("Core");
//  obj["Qt"] = qt;

  configureCMake = new ConfigureCMake(config, this);
//  configureCMake->update("/", obj);
  namePrj = new NamePrj(config, this);



  treePrj = new TreePrj(configureCMake);
  mainLayout.addWidget(namePrj, 0, 0, 1, 2);
  mainLayout.addWidget(treePrj, 1, 0);
  mainLayout.addWidget(configureCMake, 1, 1);

  setLayout(&mainLayout);
}

Widget::~Widget()
{
//  delete lPrjPath;
//  delete ePrjPath;
//  delete btnPrjPath;

//  delete lNamePrj;
//  delete eNamePrj;

//  delete componentsWdget;
//  delete componentsFiles;
//  delete cMakeListsBuild;
//  delete proBuild;
  delete treePrj;
  delete configureCMake;
}
