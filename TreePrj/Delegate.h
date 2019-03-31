#ifndef DELEGATE_H
#define DELEGATE_H

#include <QStyledItemDelegate>

class ConfigureCMake;

class Delegate : public QStyledItemDelegate
{
  Q_OBJECT

  public:
    Delegate(ConfigureCMake *configureCMake, QWidget *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

  private slots:
//    void commitAndCloseEditor();

  private:
    ConfigureCMake *configureCMake;
};

#endif // DELEGATE_H
