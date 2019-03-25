#include "SubPrj.h"

#include <QFileDialog>

SubPrj::SubPrj(QWidget *parent) : QWidget(parent)
{
  label = new QLabel("Подпроекты:");
  listView = new QListView();
  addPrj = new QPushButton("Добавить подпроект");
  listModel = new QStringListModel();
  listView->setModel(listModel);
  mainLayout.addWidget(label);
  mainLayout.addWidget(listView);
  mainLayout.addWidget(addPrj);

  connect(addPrj, &QPushButton::released, this, &SubPrj::slotAddPrj);

  setLayout(&mainLayout);
}

void SubPrj::slotAddPrj()
{
  QString curDir = config->getPrjPath();
  QStringList sourceList;
  QStringList headerList;
  QString prjDir =
      QFileDialog::getExistingDirectory(this, tr("Open project dir"), curDir);

  if (prjDir.size() == 0)
    return;

  if (prjDir.startsWith(curDir))
    {
      prjDir = prjDir.split(curDir)[1];
      while(prjDir.startsWith("/"))
        prjDir = prjDir.mid(1);
    }
  else externSubPrjList.append(prjDir);

  QStringList allList = subPrjList + externSubPrjList;
  subPrjList.append(prjDir);
  config->setSubPrjs(allList);
  listModel->setStringList(allList);

}
