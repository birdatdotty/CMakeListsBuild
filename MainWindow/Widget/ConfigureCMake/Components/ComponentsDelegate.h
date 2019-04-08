#ifndef COMPONENTSDELEGATE_H
#define COMPONENTSDELEGATE_H

#include <QStyledItemDelegate>

class ComponentsDelegate : public QStyledItemDelegate
{
public:
  ComponentsDelegate();

//  void paint(QPainter *painter, const QStyleOptionViewItem &option,
//             const QModelIndex &index) const override;
//  QSize sizeHint(const QStyleOptionViewItem &option,
//                 const QModelIndex &index) const override;
//  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
//                        const QModelIndex &index) const override;
//  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
//  void setModelData(QWidget *editor, QAbstractItemModel *model,
//                    const QModelIndex &index) const override;
  Qt::ItemFlags flags (const QModelIndex & index) const;
};

#endif // COMPONENTSDELEGATE_H
