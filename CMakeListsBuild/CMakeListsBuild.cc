#include "CMakeListsBuild.h"
#include "Config.h"

#include <QFile>


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

QString CMakeListsBuild::buildCtxApp()
{
  QString project = config->getPrjName();
  QString header = "cmake_minimum_required(VERSION 3.1)\n"
                   "project(%1 LANGUAGES CXX)\n"
                   "set(CMAKE_INCLUDE_CURRENT_DIR ON)\n"
                   "set(CMAKE_AUTOMOC ON)\n"
                   "set(CMAKE_AUTORCC ON)\n"
                   "set(CMAKE_CXX_STANDARD 11)\n"
                   "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
                   "\n"
                   "%2\n"
                   "%5"
                   "add_executable(%3)\n"
                   "\n"
                   "target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)\n"
                   "target_link_libraries(%4)\n"
                    "install(TARGETS ${PROJECT_NAME} DESTINATION bin)\n";

  files = config->getSourceList();
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
  QString ctx = header.arg(project, packages, filesStr, library, subPrjStr);

  return ctx;
}

QString CMakeListsBuild::buildCtxStaticLib()
{
  QString project = config->getPrjName();
  QString header = "cmake_minimum_required(VERSION 3.12)\n"
      "\n"
      "project(%1)\n"
      "\n"
      "set(CMAKE_INCLUDE_CURRENT_DIR ON)\n"
      "set(CMAKE_AUTOMOC ON)\n"
      "set(CMAKE_AUTORCC ON)\n"
      "set(CMAKE_CXX_STANDARD 17)\n"
      "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
      "\n"
      "%2\n" // <-------------------------------
      "set (sources %3)\n" // <-------------------------------
      "#add_library(%1 SHARED ${sources}) # dynamic lib (*.so)\n"
      "#add_library(%1 STATIC ${sources}) # static lib (*.a)\n"
      "#add_library(%1 MODULE ${sources}) # module lib (*.so)\n"
      "add_library(%1 STATIC ${sources})\n" // <-------------------------------
      "target_link_libraries(%1 %4)\n"
      "\n"
      "#install(TARGETS ${PROJECT_NAME} DESTINATION lib)\n"
      "#  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib\n"
      "#  PERMISSIONS OWNER_EXECUTE)\n"
      "install(TARGETS ${PROJECT_NAME} DESTINATION lib)\n"
      "install(FILES %5 DESTINATION include)\n";

  files = config->getSourceList();
  QStringList headers = config->getHeaderList();
  QStringList components = config->getComponents();
  QString packages,
          library = "${PROJECT_NAME}" ,
          filesStr = files.join(" "),
          headersStr = headers.join(" ");

  if (components.size() > 0)
    {
      packages = "find_package(Qt5 COMPONENTS " + components.join(" ") + " REQUIRED)\n";
      library = "Qt5::" + components.join(" Qt5::");
    }
  QString ctx = header.arg(project, packages, filesStr, library, headersStr);

  return ctx;
}

QString CMakeListsBuild::buildCtxDinamicLib()
{
  QString project = config->getPrjName();
  QString header = "cmake_minimum_required(VERSION 3.12)\n"
      "\n"
      "project(%1)\n"
      "\n"
      "set(CMAKE_INCLUDE_CURRENT_DIR ON)\n"
      "set(CMAKE_AUTOMOC ON)\n"
      "set(CMAKE_AUTORCC ON)\n"
      "set(CMAKE_CXX_STANDARD 17)\n"
      "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
      "\n"
      "%2\n" // <-------------------------------
      "set (sources %3)\n" // <-------------------------------
      "#add_library(%1 SHARED ${sources}) # dynamic lib (*.so)\n"
      "#add_library(%1 STATIC ${sources}) # static lib (*.a)\n"
      "#add_library(%1 MODULE ${sources}) # module lib (*.so)\n"
      "add_library(%1 SHARED ${sources})\n" // <-------------------------------
      "target_link_libraries(%1 %4)\n"
      "\n"
      "#install(TARGETS ${PROJECT_NAME} DESTINATION lib)\n"
      "#  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib\n"
      "#  PERMISSIONS OWNER_EXECUTE)\n"
      "install(TARGETS ${PROJECT_NAME} DESTINATION lib)\n"
      "install(FILES %5 DESTINATION include)\n";

  files = config->getSourceList();
  QStringList headers = config->getHeaderList();
  QStringList components = config->getComponents();
  QString packages,
          library = "${PROJECT_NAME}" ,
          filesStr = files.join(" "),
          headersStr = headers.join(" ");

  if (components.size() > 0)
    {
      packages = "find_package(Qt5 COMPONENTS " + components.join(" ") + " REQUIRED)\n";
      library = "Qt5::" + components.join(" Qt5::");
    }
  QString ctx = header.arg(project, packages, filesStr, library, headersStr);

  return ctx;
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
  QString mode = config->getPrjMode();
  QString file = config->getPrjPath() + "/CMakeLists.txt";
  if (mode == "App")
    config->writeFile(file, buildCtxApp());
  if (mode == "StaticLib")
    config->writeFile(file, buildCtxStaticLib());
  if (mode == "DinamicLib")
    config->writeFile(file, buildCtxDinamicLib());
}
