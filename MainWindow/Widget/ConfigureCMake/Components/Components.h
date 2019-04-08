#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListView>
#include <QLabel>

#include <QJsonArray>

#include "Config/Config.h"

class ComponentsModel;


class Components : public QWidget
{
  Q_OBJECT
  public:
    explicit Components(QWidget *parent = nullptr);

  signals:

  public slots:
    void update(QJsonArray);

  private:
    QVBoxLayout mainLayout;
    QListView* listView;
    QLabel* label;
    ComponentsModel *listModel;
};

#endif // COMPONENTS_H
