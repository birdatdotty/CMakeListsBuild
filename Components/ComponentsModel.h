#ifndef MODEL_H
#define MODEL_H

#include <QStringListModel>
#include <QPersistentModelIndex>
#include <QSet>
#include <Config.h>

class ComponentsModel: public QStringListModel
{
  Q_OBJECT
  public:
    ComponentsModel( QObject* parent = nullptr);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant data(const QModelIndex &index, int role) const;
    void getComponents();

  public slots:
    void update(QStringList components);

  private:
      QSet<QPersistentModelIndex> checkedItems;
};

#endif // MODEL_H
