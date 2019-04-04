#include "SubPrj.h"
#include "../TreePrj/TreeItem.h"

#include <QFileDialog>
#include <QJsonObject>

SubPrj::SubPrj(QWidget *parent) : QWidget(parent)
{
  label = new QLabel("Подпроекты:");
  listView = new QListView();
  addPrj = new QPushButton("Добавить подпроект");
  listModel = new QStringListModel();
  listView->setModel(listModel);
  mainLayout.addWidget(label);
  mainLayout.addWidget(listView);
  mainLayout.addWidget(addPrj);

  connect(addPrj, &QPushButton::released, this, &SubPrj::slotAddPrj);

  setLayout(&mainLayout);
}

void SubPrj::update(QJsonArray arr)
{
  subPrjList.clear();
  for(QJsonValue value: arr)
    subPrjList.insert(value.toString());

  config->setSubPrjs(subPrjList.toList());
  listModel->setStringList(subPrjList.toList());
}

#include <QDebug>
void SubPrj::slotAddPrj()
{
  QString mainDir = config->getMainPrjPath();
  QStringList prjDirList = config->getPrjPath().split("/");
  if (prjDirList.size() < 2)
    return;

  prjDirList.pop_front();
  prjDirList.pop_front();
  QString prjDir = prjDirList.join("/");
  QString curDir = mainDir + "/" + prjDir;
  QStringList sourceList;
  QStringList headerList;
  QString prjPath =
      QFileDialog::getExistingDirectory(this,
                                        tr("Open project dir"),
                                        curDir);

  if (prjPath.size() == 0)
    return;

  if (prjPath.startsWith(mainDir))
    {
      prjPath = prjPath.split(curDir)[1];
      while(prjPath.startsWith("/"))
        prjPath = prjPath.mid(1);
      subPrjList.insert(prjPath);
    }
  else externSubPrjList.insert(prjPath);

  QStringList allList;
  for (auto prj: subPrjList)
    allList.append(prj);

  for (auto prj: externSubPrjList)
    allList.append(prj);

  config->setSubPrjs(allList);
  listModel->setStringList(allList);
  QJsonArray jsonSubPrjList;
  for (QString str: subPrjList)
    jsonSubPrjList.append(str);

  QModelIndex index = config->getCurIndex();
  QJsonObject json = qvariant_cast<QJsonObject>(index.data());
  json["dirs"] = jsonSubPrjList;
  QVariant variantJson = qVariantFromValue(json);

  const QAbstractItemModel* constModel = index.model();
  QAbstractItemModel* model = const_cast<QAbstractItemModel*>(constModel);
qInfo() << "index:" << index;
  model->setData(index, variantJson);
}
