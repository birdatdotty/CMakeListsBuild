#include "ComponentsModel.h"

#include <QColor>

#include "Config.h"

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

  config->setComponents(list);
}

