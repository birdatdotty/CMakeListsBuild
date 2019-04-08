#include "ProBuild.h"

#include "Config/Config.h"


ProBuild::ProBuild(QWidget *parent)
  : QWidget(parent),
    filePath(new QLineEdit),
    create(new QPushButton("Создать prj.pro"))
{
  connect(filePath, &QLineEdit::textChanged, [=](QString text){
    create->setEnabled(text.size() > 0);
  });

  connect(create, &QPushButton::released,
          [=](){config->writeFile(config->getPrjPath() + "/prj.pro", buildCtx());});

  connect(config, &Config::update, [=](){
      bool status = (config->getPrjPath().size() > 0) &&
                    (config->getPrjName().size() > 0) &&
                    (config->getSourceList().size() > 0);

      create->setEnabled(status);
    });


  mainLayout.addWidget(create);
  setLayout(&mainLayout);

}

ProBuild::~ProBuild()
{

}

QString ProBuild::buildCtx()
{
  QString project = "prj1";
  QString header = "QT       += %1\n"
                   "TARGET = %2\n"
                   "TEMPLATE = app\n"
                   "CONFIG += c++11\n"
                   "SOURCES +=\\\n"
                   "%3\n\n"
                   "HEADERS +=\\\n"
                   "%4"
                   "\n\n"
                   "# Default rules for deployment."
                   "qnx: target.path = /tmp/$${TARGET}/bin"
                   "else: unix:!android: target.path = /opt/$${TARGET}/bin"
                   "!isEmpty(target.path): INSTALLS += target\n";

  files = config->getSourceList();
  QString packages = config->getComponents().join(" ").toLower(),
          sourceStr = "        " + files.join(" \\\n        "),
          headerStr = "        " + files.join(" \\\n        ");

  QString ctx = header.arg(packages, project, sourceStr, headerStr);

return ctx;
}
