#include "ExtendedLib.h"

#include <QStringListModel>
#include <QFileDialog>
#include <QAction>

#include "Config.h"


ExtendedLib::ExtendedLib(QWidget* parent)
  : QWidget(parent)
{
  label = new QLabel("Библиотеки(pkgconfig):");
  listView = new QListView();
  addFile = new QPushButton("Добавить библиотеку (*.pc)");
  listModel = new QStringListModel();
  listView->setModel(listModel);
  mainLayout.addWidget(label);
  mainLayout.addWidget(listView);
  mainLayout.addWidget(addFile);

  connect(addFile, &QPushButton::released, this, &ExtendedLib::slotAddFile);

  setLayout(&mainLayout);
}

#include <QDebug>
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
