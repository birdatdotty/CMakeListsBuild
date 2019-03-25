#include "ExtendedLib.h"

#include <QFileDialog>
#include "Config.h"

ExtendedLib::ExtendedLib(QWidget *parent) : QWidget(parent)
{
  addInclude = new QPushButton(tr("add include..."));
  addLib = new QPushButton(tr("add lib..."));

  mainLayout.addWidget(addLib);
  mainLayout.addWidget(addInclude);

  connect(addLib, &QPushButton::released, this, &ExtendedLib::slotAddLib);

  setLayout(&mainLayout);
}

void ExtendedLib::slotAddLib()
{
  QString dir = config->getPrjPath();
  QStringList sourceList;
  QStringList headerList;
  QStringList files = QFileDialog::getOpenFileNames(this, tr("Open lib..."),
                                                    dir,
                                                    tr("lib for project (*.so *.dll *.a *.lib)"));

  if (files.size() == 0)
    return;

  QStringList fileList;

//  foreach (QString fileItr, files)
//    {
//      QString file = fileItr.split(dir)[1];
//      while (file.startsWith("/"))
//        file = file.split("/")[1];

//      fileList.append(file);
//      if (file.endsWith(".cc") || file.endsWith(".cpp"))
//        {
//          sourceList.append(file);
//        }

//      if (file.endsWith(".h") )
//        headerList.append(file);
//    }
//  config->setSourceList(sourceList);
//  config->setHeaderList(headerList);

//  listModel->setStringList(fileList);

}

void ExtendedLib::slotAddInclude()
{

}
