#ifndef CONFIGURECMAKE_H
#define CONFIGURECMAKE_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "Config.h"

class CMakeListsBuild;
class Components;
class ComponentsFiles;
class ProBuild;
class CheckMode;
class SubPrj;
class ExtendedLib;
class TreePrj;


class ConfigureCMake : public QWidget
{
  Q_OBJECT
  public:
    explicit ConfigureCMake(Config *config, QWidget *parent = nullptr);

  private:
    QGridLayout mainLayout;
    CMakeListsBuild *cMakeListsBuild;
    ProBuild *proBuild;
    Components *componentsWdget;
    ComponentsFiles *componentsFiles;

    SubPrj *subPrj;
    CheckMode *checkMode;
    ExtendedLib *extendedLib;
    QLabel *lPrjPath, *lNamePrj;
    QLineEdit *ePrjPath, *eNamePrj;
    QPushButton *btnPrjPath;

    Config *config;

  public slots:
    void update(QString, QJsonObject);
};

#endif // CONFIGURECMAKE_H
