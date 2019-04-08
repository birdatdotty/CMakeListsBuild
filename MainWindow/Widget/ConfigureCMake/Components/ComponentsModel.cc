#include "ComponentsModel.h"

#include <QColor>
#include <QJsonArray>

#include "Config/Config.h"

ComponentsModel::ComponentsModel(QObject *parent)
  : QStringListModel(parent)
{

}

Qt::ItemFlags ComponentsModel::flags(const QModelIndex &index) const
{
  Qt::ItemFlags defaultFlags = QStringListModel::flags(index) ;

  if (index.isValid()){
      return defaultFlags | Qt::ItemIsUserCheckable;
  }
  return defaultFlags;
}

#include <QDebug>
bool ComponentsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if(!index.isValid() || role != Qt::CheckStateRole)
      return false;

  if(value == Qt::Checked)
    {
      checkedItems.insert(index);
      getComponents();
    }
  else
    {
      checkedItems.remove(index);
      getComponents();
    }


  emit dataChanged(index, index);
  return true;
}

QVariant ComponentsModel::data(const QModelIndex &index, int role) const
{

  if (!index.isValid())
      return QVariant();

  if(role == Qt::CheckStateRole)
    {
      return checkedItems.contains(index) ?
            Qt::Checked : Qt::Unchecked;
    }

  else if(role == Qt::BackgroundColorRole)
      return checkedItems.contains(index) ?
                  QColor("#ffffb2") : QColor("#ffffff");

  return QStringListModel::data(index, role);
}

void ComponentsModel::getComponents()
{
  QStringList list;
  for (auto item: checkedItems)
    list.append(item.data().toString());

  qInfo() << __LINE__ << "void ComponentsModel::getComponents()";
  QJsonArray arr;
  for (QString str: list)
    arr.append(str);

  QModelIndex mainIndex = config->getCurIndex();
  QVariant data = mainIndex.data();
  if (data.canConvert<QJsonObject>())
    {
      QJsonObject json = qvariant_cast<QJsonObject>(data);

      qInfo() << __LINE__ << arr;
      json["Qt"] = arr;
      qInfo() << __LINE__ << json;

  ////////////////////////////////////////////////////////////////
      const QAbstractItemModel* constModel = mainIndex.model();
      QAbstractItemModel* model = const_cast<QAbstractItemModel*>(constModel);
      QVariant variantJson = qVariantFromValue(json);
      model->setData(mainIndex, variantJson);
    }

  config->setComponents(list);
}

void ComponentsModel::update(QStringList components)
{
  QStringList listComponents = stringList();
  for (int i = 0; i < listComponents.size(); i++)
    {
      QString component = listComponents[i];
      if (components.contains(component))
        checkedItems.insert(index(i));
      else
        checkedItems.remove(index(i));
    }
}

