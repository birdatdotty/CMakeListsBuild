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
  listModel = new ComponentsModel(this);
  listModel->setStringList(settingsComponents.split(" "));
  listView->setModel(listModel);

  ComponentsDelegate *delegate = new ComponentsDelegate;
  listView->setItemDelegate(delegate);

  setLayout(&mainLayout);
}

#include <QDebug>
void Components::update(QJsonArray arr)
{
  qInfo() << arr;
  QStringList list;
  for (QJsonValue value: arr)
    list.append(value.toString());

  listModel->update(list);
}

