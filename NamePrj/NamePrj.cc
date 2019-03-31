#include "NamePrj.h"

#include "Config.h"

NamePrj::NamePrj(Config *config, QWidget *parent)
  : QWidget(parent)
{
  lPrjPath = new QLabel("Проект:");
  ePrjPath = new QLineEdit(config->getPrjPath());
  btnPrjPath = new QPushButton("...");

  mainLayout.addWidget(lPrjPath);
  mainLayout.addWidget(ePrjPath);
  mainLayout.addWidget(btnPrjPath);

  connect(btnPrjPath, &QPushButton::released, config, &Config::browseMainPrjPath);
  connect(ePrjPath, &QLineEdit::textChanged, config, &Config::setMainPrjPath);
  connect(config, &Config::updateMainPrjPath, ePrjPath, &QLineEdit::setText);



  setLayout(&mainLayout);
}
