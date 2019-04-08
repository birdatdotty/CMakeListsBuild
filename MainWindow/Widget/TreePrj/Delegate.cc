#include "Delegate.h"
#include "TreeItem.h"
#include "../ConfigureCMake/ConfigureCMake.h"

#include <QPainter>
#include <QJsonObject>

Delegate::Delegate(ConfigureCMake *configureCMake, QWidget *parent)
  : QStyledItemDelegate(parent),
    configureCMake(configureCMake)
{

}
void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  if (index.data().canConvert<QJsonObject>()) {
      QJsonObject json = qvariant_cast<QJsonObject>(index.data());
      if (option.state & QStyle::State_Selected)
        {
          painter->fillRect(option.rect, option.palette.highlight());
          QVariant data = index.data();
          QString path = index.data(Qt::UserRole).toString();
          config->setCurIndex(index);

          configureCMake->update(path, qvariant_cast<QJsonObject>(data));
        }
      painter->drawText(option.rect, json["name"].toString());
      return;
  } else {
      QStyledItemDelegate::paint(painter, option, index);
  }
}
