#include "TreeItem.h"
#include "Config.h"
#include <QJsonDocument>
#include <QJsonObject>


TreeItem::TreeItem(const QString path,
                   const QVariant &data,
                   TreeItem *parentItem)
  : m_itemData(data),
    m_parentItem(parentItem),
    path(path)
{

}

TreeItem::~TreeItem()
{
  qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
  m_childItems.append(item);
  item->m_parentItem = this;
}

TreeItem *TreeItem::child(int row)
{
  return m_childItems.value(row);
}

int TreeItem::childCount() const
{
  return m_childItems.count();
}

int TreeItem::columnCount() const
{
  return 1;
}

QVariant TreeItem::data(int role) const
{
  if (role == Qt::UserRole)
    {
      QString curPuth = getPath();
      return curPuth;
    }

  return m_itemData;
}

TreeItem *TreeItem::parentItem()
{
  return m_parentItem;
}

#include <QDebug>
void TreeItem::update(const QVariant &newData)
{
  m_itemData = newData;
  QString initFile = config->getMainPrjPath1() + getPath() + "/init.json";
  QJsonObject jsonObj = qvariant_cast<QJsonObject>(newData);
  QJsonDocument doc(jsonObj);
  QString strJson(doc.toJson(QJsonDocument::Compact));
  config->writeFile(initFile, strJson);
}

QString TreeItem::getPath() const
{
  if (m_parentItem)
    return m_parentItem->getPath() + "/" + path;

  return "";
}

int TreeItem::row() const
{
  if (m_parentItem)
    return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

  return 0;
}
