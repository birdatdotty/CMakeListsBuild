#include "ComponentsDelegate.h"

ComponentsDelegate::ComponentsDelegate()
{

}

Qt::ItemFlags ComponentsDelegate::flags(const QModelIndex &/*index*/) const
{
  return Qt::ItemIsUserCheckable;
}
