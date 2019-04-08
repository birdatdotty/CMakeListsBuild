#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QString>
#include <QList>
#include <QMap>
#include <QSettings>
#include <QModelIndex>
#include <QJsonObject>

class Config;
extern Config* config;

typedef void(*f)();

class Config: public QObject
{
  Q_OBJECT
public:
  explicit Config();

  QSettings *setting;

public slots:
  void setMainPrjPath(const QString& str);
  void setPrjPath(const QString& str);
  void setPrjName(const QString& str);
  void setComponents(const QStringList newComponents);
  void setSourceList(const QStringList newSourceList);
  void setHeaderList(const QStringList newHeaderList);
  void setSubPrjs(const QStringList newSubPrjs);
  void setPrjMode(const QString mode);
  void setPkgList(const QStringList newPkgList);
  void browsePrjPath();
  void browseMainPrjPath();

  QString getMainPrjPath() const;
  QString getMainPrjPath1() const;
  QString getPrjPath() const;
  QString getPrjName() const;
  QString getPrjMode() const;
  QStringList getComponents() const;
  QStringList getSourceList() const;
  QStringList getHeaderList() const;
  QStringList getSubPrjs() const;
  void setCurIndex(const QModelIndex &index);
  QModelIndex getCurIndex();
  QJsonObject openInit(QString file);


public:
  bool writeFile(QString file, QString data);

signals:
  void update();
  void updatePrjPath(QString);
  void updateMainPrjPath(QString);

private:
  QString mainPrjPath;
  QString prjMode;
  QString prjPath;
  QString prjName;
  QStringList components;
  QStringList headerList;
  QStringList sourceList;
  QStringList subPrjs;
  QStringList pkgList;

  QModelIndex index;
};

#endif // CONFIG_H
