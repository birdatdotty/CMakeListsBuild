#include "TreeItem.h"

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

#include <QDebug>
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
