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

void ComponentsFiles::update(QJsonArray sources, QJsonArray headers)
{
  QStringList files;
  for (int i = 0; i < sources.size(); i++)
    {
      QString item = sources[i].toString();
      files << item;
    }

  for (QJsonValue value: headers)
    files.append(value.toString());

  slotSetFiles(files);
}
#include <QDebug>
void ComponentsFiles::slotAddFile()
{
  QString dir = config->getMainPrjPath1() + config->getPrjPath();
  qInfo() << "dir:" << dir;
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

  QModelIndex index = config->getCurIndex();
  QVariant data = index.data();
  if (data.canConvert<QJsonObject>())
    {
      QJsonObject json = qvariant_cast<QJsonObject>(data);
      QJsonArray jsonSources, jsonHeaders;
      for (QString source: sourceList)
        jsonSources.append(source);
      for (QString header: headerList)
        jsonHeaders.append(header);

      json["headers"] = jsonHeaders;
      json["sources"] = jsonSources;
      qInfo() << __LINE__ << json;

  ////////////////////////////////////////////////////////////////
      const QAbstractItemModel* constModel = index.model();
      QAbstractItemModel* model = const_cast<QAbstractItemModel*>(constModel);
      QVariant variantJson = qVariantFromValue(json);
      model->setData(index, variantJson);
    }
  qInfo() << __LINE__ << config->getCurIndex().data();


  listModel->setStringList(fileList);

}
