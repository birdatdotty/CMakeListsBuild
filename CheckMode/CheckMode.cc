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
  udpateJson();
  config->setPrjMode("App");
}

void CheckMode::selectRadioStaticLib()
{
  mode = StaticLib;
  udpateJson();
  config->setPrjMode("StaticLib");
}

void CheckMode::selectRadioDinamicLib()
{
  mode = DinamicLib;
  udpateJson();
  config->setPrjMode("DinamicLib");
}

void CheckMode::udpateJson()
{
  QModelIndex index = config->getCurIndex();
  QJsonObject json = qvariant_cast<QJsonObject>(index.data());
  if (mode == App)
    json["mode"] = "App";
  else if (mode == StaticLib)
    json["mode"] = "StaticLib";
  else if (mode == DinamicLib)
    json["mode"] = "DinamicLib";
  QVariant variantJson = qVariantFromValue(json);

  const QAbstractItemModel* constModel = index.model();
  QAbstractItemModel* model = const_cast<QAbstractItemModel*>(constModel);
  model->setData(index, variantJson);
}

void CheckMode::updateMode(QString mode)
{
  if (mode == "App")
    {
      mode = App;
      radioApp->setChecked(true);
      return;
    }
  if (mode == "StaticLib")
    {
      mode = StaticLib;
      radioStaticLib->setChecked(true);
      return;
    }
  if (mode == "DinamicLib")
    {
      mode = DinamicLib;
      radioDinamicLib->setChecked(true);
      return;
    }

}
