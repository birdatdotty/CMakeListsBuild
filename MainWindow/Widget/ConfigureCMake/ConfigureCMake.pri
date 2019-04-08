HEADERS += \
    $$PWD/ConfigureCMake.h

SOURCES += \
    $$PWD/ConfigureCMake.cc

include($$PWD/ExtendedLib/ExtendedLib.pri)
include($$PWD/CMakeListsBuild/CMakeListsBuild.pri)
include($$PWD/ProBuild/ProBuild.pri)
include($$PWD/Components/Components.pri)
include($$PWD/ComponentsFiles/ComponentsFiles.pri)
include($$PWD/CheckMode/CheckMode.pri)
include($$PWD/SubPrj/SubPrj.pri)
