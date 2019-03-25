#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListView>
#include <QLabel>

#include "Config.h"


class Components : public QWidget
{
  Q_OBJECT
  public:
    explicit Components(QWidget *parent = nullptr);

  signals:

  public slots:
  private:
    QVBoxLayout mainLayout;
    QListView* listView;
    QLabel* label;
};

#endif // COMPONENTS_H
