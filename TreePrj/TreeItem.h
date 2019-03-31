#ifndef TREEITEM_H
#define TREEITEM_H

#include <QObject>
#include <QList>

class TreeItem
{
  public:
    explicit TreeItem(const QString path,
                      const QVariant &data,
                      TreeItem *parentItem = nullptr);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int role) const;
    int row() const;
    TreeItem *parentItem();

  private:
    QList<TreeItem*> m_childItems;
    QVariant m_itemData;
    TreeItem *m_parentItem;
    QString path;
    QString getPath() const;
};

#endif // TREEITEM_H
