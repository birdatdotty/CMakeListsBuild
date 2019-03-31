#ifndef TREEPRJ_H
#define TREEPRJ_H

#include "TreeItem.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTreeView>
#include <QJsonObject>

class TreeModel;
class ConfigureCMake;
class Delegate;

class TreePrj : public QWidget
{
  Q_OBJECT
  public:
    explicit TreePrj(ConfigureCMake *configureCMake, QWidget *parent = nullptr);

  private:
    QVBoxLayout mainLayout;

    QLabel *label;
    QTreeView *view;
    TreeModel *model;
    Delegate *delegate;

    QJsonObject openInit(QString file);
    void openByPath(QString path, TreeItem* parent = nullptr);

  private slots:
    void initNewTreeItem(QString mainPath);
};

#endif // TREEPRJ_H
