#include "ComponentsFiles.h"

#include <QStringListModel>
#include <QFileDialog>
#include <QAction>

#include "Config.h"


ComponentsFiles::ComponentsFiles(QWidget* parent)
  : QWidget(parent)
{
  label = new QLabel("Файлы:");
  listView = new QListView();
  addFile = new QPushButton("Добавить файл");
  listModel = new QStringListModel();
  listView->setModel(listModel);
  mainLayout.addWidget(label);
  mainLayout.addWidget(listView);
  mainLayout.addWidget(addFile);

  connect(addFile, &QPushButton::released, this, &ComponentsFiles::slotAddFile);

  setLayout(&mainLayout);
}

void ComponentsFiles::slotAddFile()
{
  QString dir = config->getPrjPath();
  QStringList sourceList;
  QStringList headerList;
  QStringList files = QFileDialog::getOpenFileNames(this, tr("Open File"),
                                                  dir,
                                                  tr("files for project (*.cc *.cpp *.h)"));

  QStringList fileList;
  foreach (QString fileItr, files)
    {
      QString file = fileItr.split(dir)[1];
      while (file.startsWith("/"))
        file = file.split("/")[1];

      fileList.append(file);
      if (file.endsWith(".cc") || file.endsWith(".cpp"))
        {
          sourceList.append(file);
        }

      if (file.endsWith(".h") )
        headerList.append(file);
    }
  config->setSourceList(sourceList);
  config->setHeaderList(headerList);

  listModel->setStringList(fileList);
}
