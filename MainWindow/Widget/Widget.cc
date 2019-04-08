#include "Widget.h"

//#include "ConfigureCMake/CMakeListsBuild/CMakeListsBuild.h"
//#include "ConfigureCMake/ProBuild/ProBuild.h"
//#include "ConfigureCMake/CheckMode/CheckMode.h"
//#include "ConfigureCMake/SubPrj/SubPrj.h"
//#include "ConfigureCMake/ExtendedLib/ExtendedLib.h"
#include "TreePrj/TreePrj.h"
#include "NamePrj/NamePrj.h"

#include "ConfigureCMake/ConfigureCMake.h"


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
