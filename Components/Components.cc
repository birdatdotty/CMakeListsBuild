#include "Components.h"
#include "ComponentsDelegate.h"
#include "ComponentsModel.h"

#include <QAction>
#include <QStringListModel>

Components::Components(QWidget *parent)
  : QWidget(parent)
{
  QSettings * settings = config->setting;
  QString settingsComponents =  settings->value("components","Core Widgets Gui").toString();
  settings->sync();
  label = new QLabel("компоненты:");
  listView = new QListView();
  mainLayout.addWidget(label);
  mainLayout.addWidget(listView);
  ComponentsModel *listModel = new ComponentsModel(this);
  listModel->setStringList(settingsComponents.split(" "));
  listView->setModel(listModel);

  ComponentsDelegate *delegate = new ComponentsDelegate;
  listView->setItemDelegate(delegate);

  setLayout(&mainLayout);
}

