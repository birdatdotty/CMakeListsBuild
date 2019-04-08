#ifndef SUBPRJ_H
#define SUBPRJ_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListView>
#include <QLabel>
#include <QStringListModel>
#include <QPushButton>
#include <QJsonArray>
#include <QSet>

#include "Config/Config.h"

class SubPrj : public QWidget
{
  Q_OBJECT
  public:
    explicit SubPrj(QWidget *parent = nullptr);

  signals:

  public slots:
    void update(QJsonArray);

  private:
    QVBoxLayout mainLayout;
    QListView* listView;
    QStringListModel* listModel;
    QLabel* label;
    QPushButton *addPrj;
    QSet<QString> subPrjList,
                  externSubPrjList;

  private slots:
    void slotAddPrj();
};

#endif // SUBPRJ_H
