#include "TreeModel.h"
#include "TreeItem.h"

#include "../ConfigureCMake.h"

TreeModel::TreeModel(ConfigureCMake *configureCMake)
  : configureCMake(configureCMake)
{
  QVariant rootData;
  rootData = "Title";
  rootItem = new TreeItem("/", rootData);

  TreeItem *child2 = new TreeItem("child2", rootData);
  TreeItem *child3 = new TreeItem("child3", rootData);
  rootItem->appendChild(child2);
  child2->appendChild(child3);
}

TreeModel::~TreeModel()
{
    delete rootItem;
}
//configureCMake->update("/tmp", obj);
int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
      return rootItem->columnCount();
}

void TreeModel::update(TreeItem *newRoot)
{
beginResetModel();
  TreeItem *old = rootItem;
  rootItem = newRoot;
  delete old;
endResetModel();
//  dataChanged(QModelIndex(),QModelIndex());
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
      {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        return item->data(Qt::DisplayRole);
      }
    if (role == Qt::UserRole)
      {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        return item->data(Qt::UserRole);
      }
    return QVariant();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}
