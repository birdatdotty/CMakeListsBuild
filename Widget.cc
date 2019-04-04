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


Widget::Widget(Config *config, QString path, QWidget *parent)
  : QWidget(parent),
    config (config)
{

  configureCMake = new ConfigureCMake(config, this);
  namePrj = new NamePrj(config, this);



  treePrj = new TreePrj(configureCMake);
  mainLayout.addWidget(namePrj, 0, 0, 1, 2);
  mainLayout.addWidget(treePrj, 1, 0);
  mainLayout.addWidget(configureCMake, 1, 1);

  if (path.size()>0)
    config->setMainPrjPath(path);

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
