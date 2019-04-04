#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>

class TreeItem;
class ConfigureCMake;

class TreeModel : public QAbstractItemModel
{
  public:
    TreeModel(ConfigureCMake *configureCMake);
    ~TreeModel() override;

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

  public slots:
    void update(TreeItem* newRoot);

  private:
    TreeItem *rootItem;
    ConfigureCMake *configureCMake;
    void openByPath(QString path, TreeItem* parent);
};

#endif // TREEMODEL_H
