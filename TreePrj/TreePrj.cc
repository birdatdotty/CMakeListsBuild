#include "TreePrj.h"
#include "TreeModel.h"
#include "Delegate.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>

#include "Config.h"

void TreePrj::openByPath(QString path, TreeItem* parent)
{
  QJsonObject json = config->openInit(path + "/init.json");
  QVariant data = QVariant::fromValue(json);
  TreeItem *treeItem = new TreeItem(json["name"].toString() ,data);
  parent->appendChild(treeItem);
  for (QJsonValue value: json["dirs"].toArray())
    openByPath(path+"/"+value.toString(), treeItem);
}

void TreePrj::initNewTreeItem(QString mainPath)
{
  TreeItem *root = new TreeItem("/", "root");
  openByPath(mainPath, root);

  model->update(root);
}

TreePrj::TreePrj(ConfigureCMake *configureCMake, QWidget *parent) : QWidget(parent)
{
  label = new QLabel("Структура:");
  view = new QTreeView();
  model = new TreeModel(configureCMake);


  mainLayout.addWidget(label);
  mainLayout.addWidget(view);
  view->setModel(model);
  delegate = new Delegate(configureCMake);
  view->setItemDelegate(delegate);
  connect(config, &Config::updateMainPrjPath, this, &TreePrj::initNewTreeItem);

  setLayout(&mainLayout);
}

//QJsonObject TreePrj::openInit(QString file)
//{
//  QJsonObject jsonObject, blankJsonObject;
//  QFile fd(file);
//  if (!fd.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//      QStringList fileSplit = file.split("/");
//      jsonObject["name"] = fileSplit[fileSplit.size()-2];

//      QString ctx = QJsonDocument(jsonObject).toJson();
//      if (!config->writeFile(file, ctx))
//        return blankJsonObject;
//      else
//        return jsonObject;
//    }

//  const QByteArray json = fd.readAll();
//  jsonObject = QJsonDocument::fromJson(json).object();

//  return jsonObject;
//}
