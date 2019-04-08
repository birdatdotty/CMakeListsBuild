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

  private:
    ConfigureCMake *configureCMake;
};

#endif // DELEGATE_H
