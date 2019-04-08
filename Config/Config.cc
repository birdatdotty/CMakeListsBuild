#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonDocument>

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

#include <QDebug>
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

void Config::setMainPrjPath(const QString& str)
{
  mainPrjPath = str;

  update();
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

QString Config::getMainPrjPath1() const
{

  bool endSep = (mainPrjPath.endsWith("/"));

  QStringList splitMainPath = mainPrjPath.split("/");
  splitMainPath.removeLast();
  if (endSep)
    splitMainPath.removeLast();

  return splitMainPath.join("/");
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

void Config::setCurIndex(const QModelIndex &newIndex)
{
  index = newIndex;
}

QModelIndex Config::getCurIndex()
{
  return index;
}

QJsonObject Config::openInit(QString file)
{
  QJsonObject jsonObject, blankJsonObject;
  QFile fd(file);
  if (!fd.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QStringList fileSplit = file.split("/");
      jsonObject["name"] = fileSplit[fileSplit.size()-2];

      QString ctx = QJsonDocument(jsonObject).toJson();
      if (!config->writeFile(file, ctx))
        return blankJsonObject;
      else
        return jsonObject;
    }

  const QByteArray json = fd.readAll();
  jsonObject = QJsonDocument::fromJson(json).object();

  return jsonObject;

}

bool Config::writeFile(QString file, QString data)
{
  QFile fd(file);
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
