#include "ExtendedLib.h"

#include <QStringListModel>
#include <QFileDialog>
#include <QAction>

#include "Config.h"

#include <QDebug>
ExtendedLib::ExtendedLib(QWidget* parent)
  : QWidget(parent)
{
  label = new QLabel("Библиотеки(pkgconfig):");
  listView = new QListView();
  addFile = new QPushButton("Добавить библиотеку (*.pc)");
  listModel = new QStringListModel();
  qInfo() << __LINE__ << "listModel:" << listModel;
  listView->setModel(listModel);
  mainLayout.addWidget(label);
  mainLayout.addWidget(listView);
  mainLayout.addWidget(addFile);

  connect(addFile, &QPushButton::released, this, &ExtendedLib::slotAddFile);

  setLayout(&mainLayout);
}

void ExtendedLib::slotAddFile()
{
  QString dir = config->getPrjPath();
  QStringList sourceList;
  QStringList headerList;
  QStringList files = QFileDialog::getOpenFileNames(this, tr("Open File"),
                                                  "/usr/lib64/pkgconfig/",
                                                  tr("pkgconfig (*.pc)"));

  for (QString lib: files)
    pkgList.insert(lib);
  listModel->setStringList(pkgList.toList());

//  qInfo() << pkgList + files;
  listModel->setStringList(pkgList.toList());
}

#include <QDebug>
void ExtendedLib::update(QJsonArray pkgs)
{
  QStringList pkgList;
  for (QJsonValue value: pkgs)
    pkgList.append(value.toString());

  listModel->setStringList(pkgList);

}
