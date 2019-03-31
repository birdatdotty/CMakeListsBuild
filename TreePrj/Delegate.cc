#include "Delegate.h"
#include "TreeItem.h"
#include "../ConfigureCMake.h"

#include <QPainter>
#include <QJsonObject>

Delegate::Delegate(ConfigureCMake *configureCMake, QWidget *parent)
  : QStyledItemDelegate(parent),
    configureCMake(configureCMake)
{

}
#include <QDebug>
void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//  qInfo() << __FILE__ << __LINE__ << index.data();
  if (index.data().canConvert<QJsonObject>()) {
      QJsonObject json = qvariant_cast<QJsonObject>(index.data());
      if (option.state & QStyle::State_Selected)
        {
          painter->fillRect(option.rect, option.palette.highlight());
          QVariant data = index.data();
          QString path = index.data(Qt::UserRole).toString();
          qInfo() << __LINE__ << path;
//          TreeItem* item = const_cast<TreeItem*>(index);
          configureCMake->update(path, qvariant_cast<QJsonObject>(data));
        }
      painter->drawText(option.rect, json["name"].toString());
      return;
  } else {
      QStyledItemDelegate::paint(painter, option, index);
  }
}

QSize Delegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//  if (index.data().canConvert<StarRating>()) {
//      StarRating starRating = qvariant_cast<StarRating>(index.data());
//      return starRating.sizeHint();
//  } else {
      return QStyledItemDelegate::sizeHint(option, index);
//  }
}

QWidget *Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}

void Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}
