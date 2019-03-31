#include "TreePrj.h"
#include "TreeModel.h"
#include "Delegate.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

#include <QDebug>

#include "Config.h"

void TreePrj::openByPath(QString path, TreeItem* parent)
{
  QJsonObject json = openInit(path + "/init.json");
  QVariant data = QVariant::fromValue(json);
  TreeItem *treeItem = new TreeItem(json["name"].toString() ,data);
  parent->appendChild(treeItem);
  for (QJsonValue value: json["dirs"].toArray())
    openByPath(path+"/"+value.toString(), treeItem);
}

void TreePrj::initNewTreeItem(QString mainPath)
{
  QJsonObject main = openInit(mainPath + "init.json");

  QVariant v1 = QVariant::fromValue(main);

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

QJsonObject TreePrj::openInit(QString file)
{
  QJsonObject jsonObject;
  QFile fd(file);
  if (!fd.open(QIODevice::ReadOnly | QIODevice::Text))
    return jsonObject;

  const QByteArray json = fd.readAll();
  jsonObject = QJsonDocument::fromJson(json).object();

  return jsonObject;
}
