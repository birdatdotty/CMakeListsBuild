#include "CheckMode.h"
#include "Config.h"

CheckMode::CheckMode(QWidget *parent) : QWidget(parent)
{
  mode = App;
  radioApp = new QRadioButton(tr("Приложение."));
  radioStaticLib = new QRadioButton(tr("Статическая библиотека."));
  radioDinamicLib = new QRadioButton(tr("Динамическая библиотека."));

  QGroupBox *groupBox = new QGroupBox(tr("Режим сборки"));

  radiohBox.addWidget(radioApp);
  radiohBox.addWidget(radioStaticLib);
  radiohBox.addWidget(radioDinamicLib);

  groupBox->setLayout(&radiohBox);
  mainLayout.addWidget(groupBox);

  connect(radioApp, &QAbstractButton::released, this, &CheckMode::selectRadioApp);
  connect(radioStaticLib, &QAbstractButton::released, this, &CheckMode::selectRadioStaticLib);
  connect(radioDinamicLib, &QAbstractButton::released, this, &CheckMode::selectRadioDinamicLib);

  radioApp->setChecked(true);


  setLayout(&mainLayout);
}

void CheckMode::selectRadioApp()
{
  mode = App;
  config->setPrjMode("App");
}

void CheckMode::selectRadioStaticLib()
{
  mode = StaticLib;
  config->setPrjMode("StaticLib");
}

void CheckMode::selectRadioDinamicLib()
{
  mode = DinamicLib;
  config->setPrjMode("DinamicLib");
}
