#include "CMakeListsBuild.h"
#include "Config.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

CMakeListsBuild::CMakeListsBuild(QWidget *parent)
  : QWidget(parent),
    filePath(new QLineEdit),
    create(new QPushButton("Создать CMakeLists.txt"))
{
  connect(create, &QPushButton::released, this, &CMakeListsBuild::btnClick);
  connect(config, &Config::update, this, &CMakeListsBuild::update);


  mainLayout.addWidget(create);
  setLayout(&mainLayout);
}

CMakeListsBuild::~CMakeListsBuild()
{
  delete label;
}
#include <QDebug>
QString CMakeListsBuild::buildCtxApp(QJsonObject json)
{
  qInfo() << __LINE__ << json;
  QJsonArray pc = json["pc"].toArray();
  QString project = config->getPrjName();
  QString header = "cmake_minimum_required(VERSION 3.12)\n"
                   "project(%1 LANGUAGES CXX)\n"
                   "\n"
                   "%2"
                   "add_executable(${PROJECT_NAME} %3)\n"
                   "\n"
                   "target_link_libraries(${PROJECT_NAME} %4)\n"
                   "install(TARGETS ${PROJECT_NAME} DESTINATION bin)\n";

  // end pkgconfig
  QString sources;
  for (QJsonValue value: json["sources"].toArray())
    sources += " " + value.toString();

  QString subPrjStr;
  QStringList components = config->getComponents();
  QStringList subPrjs = config->getSubPrjs();
  for (QString prj: subPrjs)
    subPrjStr += "add_subdirectory(" + prj + ")\n";

  QString packages,
          library = "${PROJECT_NAME}" ,
          filesStr = "${PROJECT_NAME} \"" + files.join("\" \"") + "\"";

  if (components.size() > 0)
    {
      packages = "find_package(Qt5 COMPONENTS " + components.join(" ") + " REQUIRED)\n";
      library = "${PROJECT_NAME} PRIVATE Qt5::" + components.join(" Qt5::") + " " + subPrjs.join(" ");
    }
  // pkgconfig
  QString prePackages;
  QString packageLibaries;
  if (pc.size()>0)
    {
      prePackages = "FIND_PACKAGE(PkgConfig REQUIRED)\n";
      for (QJsonValue value: pc)
        {
          QString pkg = value.toString();
          QString name = pkg.split("/").last();
          name = name.remove(QRegExp("\\W")).toUpper();
          prePackages += "PKG_CHECK_MODULES(" + name + " REQUIRED " + pkg + ")\n";
          prePackages += "INCLUDE_DIRECTORIES(${" + name + "_INCLUDE_DIRS})\n";
          prePackages += "ADD_DEFINITIONS(${" + name + "_CFLAGS_OTHER})\n\n";
          packageLibaries += " ${" + name + "} ";
          library += " ${" + name + "_LIBRARIES} ";
        }
    }

  QString ctx = header.arg(project, subPrjStr, sources, subPrjs.join(" "));

  return ctx;
}

QString CMakeListsBuild::buildCtxLib(QJsonObject json)
{
  QString mode = "STATIC";
  if (json["mode"].toString() == "DinamicLib")
    mode = "SHARED";

  QString tpl = "cmake_minimum_required(VERSION 3.12)\n"
                "\n"
                "project(%1)\n" // project
                "\n"
                "set(CMAKE_INCLUDE_CURRENT_DIR ON)\n"
                "set(CMAKE_AUTOMOC ON)\n"
                "set(CMAKE_AUTORCC ON)\n"
                "set(CMAKE_CXX_STANDARD 17)\n"
                "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
                "\n"
                "%2" // packages
                "%3" // fileStr
                "#add_library(%1 SHARED ${sources}) # dynamic lib (*.so)\n"
                "#add_library(%1 STATIC ${sources}) # static lib (*.a)\n"
                "#add_library(%1 MODULE ${sources}) # module lib (*.so)\n"
                "add_library(%1 %4 ${sources})\n" // STATIC or SHARED
                "target_link_libraries(%1 %5)\n" // library
                "\n"
                "install(TARGETS ${PROJECT_NAME} DESTINATION lib)\n"
                "%6"; // headersStr

  QJsonArray components = json["Qt"].toArray();
  QString packages/*, qtLibrary*/, library;

  QString fileStr;
  QJsonArray sources = json["sources"].toArray();
  if (sources.size() > 0)
    {
      fileStr = "set (sources";
      for (int i = 0; i < sources.size(); i++)
        {
           fileStr += " " + sources[i].toString();
        }
      fileStr += ")\n";
    }

  QString headersStr;
  QJsonArray headers = json["headers"].toArray();
  if (sources.size() > 0)
    {
      headersStr = "install(FILES";
      for (int i = 0; i < headers.size(); i++)
        {
           headersStr += " " + headers[i].toString();
        }
      headersStr += " DESTINATION include)\n";
    }

  if (components.size() > 0)
    {
      packages = "find_package(Qt5 COMPONENTS";
      for (int i = 0; i < components.size(); i++)
        {
          packages += " " + components[i].toString();
          library = "Qt5::" + components[i].toString();
        }
      packages += " REQUIRED)\n";
    }

  QJsonArray pc = json["pc"].toArray();
  if (pc.size()>0)
    {
      packages += "FIND_PACKAGE(PkgConfig REQUIRED)\n";
      for (QJsonValue value: pc)
        {
          QString pkg = value.toString();
          QString name = pkg.split("/").last();
          name = name.remove(QRegExp("\\W")).toUpper();
          packages += "PKG_CHECK_MODULES(" + name + " REQUIRED " + pkg + ")\n";
          packages += "INCLUDE_DIRECTORIES(${" + name + "_INCLUDE_DIRS})\n";
          packages += "ADD_DEFINITIONS(${" + name + "_CFLAGS_OTHER})\n\n";
          library += " ${" + name + "}";
          library += " ${" + name + "_LIBRARIES} ";
        }
      packages += "\n";
    }

  return tpl.arg(json["name"].toString(),
                 packages,
                 fileStr,
                 mode,
                 library,
                 headersStr);
}

void CMakeListsBuild::update()
{
  bool status = (config->getPrjPath().size() > 0) &&
                (config->getPrjName().size() > 0) &&
                (config->getSourceList().size() > 0);

  create->setEnabled(status);
}

void CMakeListsBuild::btnClick()
{
  QVariant data = config->getCurIndex().data();
  QString file = config->getMainPrjPath1() + "/" + config->getPrjPath() + "/CMakeLists.txt";
  if (data.canConvert<QJsonObject>())
    {
      QJsonObject json = qvariant_cast<QJsonObject>(data);
      QString mode = json["mode"].toString("App");
      if (mode == "App")
        config->writeFile(file, buildCtxApp(json));
      else
        config->writeFile(file, buildCtxLib(json));
    }
}
