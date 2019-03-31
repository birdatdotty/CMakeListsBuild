#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

#include "Config.h"

Config::Config()
{
  prjMode = "App";
  setting = new QSettings(QSettings::IniFormat, QSettings::UserScope,
                          "dotty.su", "CMakeListBuild");
}

QString Config::getPrjPath() const
{
  return prjPath;
}

QString Config::getPrjName() const
{
  return prjName;
}

QString Config::getPrjMode() const
{
  return prjMode;
}

QStringList Config::getComponents() const
{
  return components;
}

void Config::setPrjPath(const QString& str)
{
  prjPath = str;

  update();
  updatePrjPath(prjPath);
}

#include <QDebug>
void Config::setMainPrjPath(const QString& str)
{
  qInfo() << __LINE__ << "void Config::setMainPrjPath(" << str  << ")";
  mainPrjPath = str;

  update();
  qInfo() << "config:" << config;
  updateMainPrjPath(mainPrjPath);
}

void Config::setPrjName(const QString& str)
{
  prjName = str;
  update();
}

void Config::setComponents(const QStringList newComponents)
{
  components = newComponents;
  update();
}

void Config::setSourceList(const QStringList newSourceList)
{
  sourceList = newSourceList;
  update();
}

void Config::setHeaderList(const QStringList newHeaderList)
{
  headerList = newHeaderList;
  update();
}

void Config::setSubPrjs(const QStringList newSubPrjs)
{
  subPrjs = newSubPrjs;
}

void Config::setPrjMode(const QString mode)
{
  prjMode = mode;
}

void Config::setPkgList(const QStringList newPkgList)
{
  pkgList = newPkgList;
}

void Config::browsePrjPath()
{
  QString dir = QFileDialog::getExistingDirectory(nullptr, tr("Open Directory"),
                                                  "",
                                                  QFileDialog::ShowDirsOnly
                                                  | QFileDialog::DontResolveSymlinks);

  if (dir.size() > 0)
    setPrjPath(dir);
}

void Config::browseMainPrjPath()
{
  QString dir = QFileDialog::getExistingDirectory(nullptr, tr("Open Directory"),
                                                  "",
                                                  QFileDialog::ShowDirsOnly
                                                  | QFileDialog::DontResolveSymlinks);

  if (dir.size() > 0)
    setMainPrjPath(dir);
}

QString Config::getMainPrjPath() const
{
  return mainPrjPath;
}

QStringList Config::getSourceList() const
{
  return sourceList;
}

QStringList Config::getHeaderList() const
{
  return headerList;
}

QStringList Config::getSubPrjs() const
{
  return subPrjs;
}
#include <QDebug>
bool Config::writeFile(QString file, QString data)
{
  qInfo() << file << ":" << data;
  QFile fd(file);
//  QFile fd("/tmp/1.txt");
  if (fd.open(QIODevice::WriteOnly))
    {
      QTextStream out(&fd);
      out << data.toUtf8();
      fd.close();
      return true;
    }
  else
    {
      QMessageBox messageBox;
      messageBox.critical(nullptr, "Error","Файл \"" + file + "\" не записан!");
      messageBox.setFixedSize(500,200);
    }

  return false;
}
