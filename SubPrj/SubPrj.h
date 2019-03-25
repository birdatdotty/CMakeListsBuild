#ifndef SUBPRJ_H
#define SUBPRJ_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListView>
#include <QLabel>
#include <QStringListModel>
#include <QPushButton>

#include "Config.h"

class SubPrj : public QWidget
{
  Q_OBJECT
  public:
    explicit SubPrj(QWidget *parent = nullptr);

  signals:

  public slots:
  private:
    QVBoxLayout mainLayout;
    QListView* listView;
    QStringListModel* listModel;
    QLabel* label;
    QPushButton *addPrj;
    QStringList subPrjList,
                externSubPrjList;

  private slots:
    void slotAddPrj();
};

#endif // SUBPRJ_H
