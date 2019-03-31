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

#include <QDebug>
void ComponentsFiles::update(QJsonArray sources, QJsonArray headers)
{
  qInfo() << "sources:" << sources.at(2);
  qInfo() << "headers:" << headers;
  QStringList files;
  for (int i = 0; i < sources.size(); i++)
    {
      QString item = sources[i].toString();
      files << item;
    }

  for (QJsonValue value: headers)
    files.append(value.toString());

  qInfo() << files;
  slotSetFiles(files);
}

void ComponentsFiles::slotAddFile()
{
  QString dir = config->getPrjPath();
  QStringList files = QFileDialog::getOpenFileNames(this, tr("Open File"),
                                                  dir,
                                                  tr("files for project (*.cc *.cpp *.h)"));

  slotSetFiles(files);
}

void ComponentsFiles::slotSetFiles(QStringList files)
{
  QString dir = config->getPrjPath();

  QStringList sourceList;
  QStringList headerList;

  QStringList fileList;
  foreach (QString fileItr, files)
    {
      QString file = fileItr.split(dir).last();
      while (file.startsWith("/"))
        file = file.split("/").last();

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
