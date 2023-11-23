cmake_minimum_required(VERSION 3.21.1)

project(calc VERSION 1.0
                  LANGUAGES C CXX)

# Languages
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

list(APPEND QT_MODULES Qml Core Quick Gui)

# For Ubuntu
set(Qt6_DIR /home/user/Qt/6.5.0/gcc_64/lib/cmake/Qt6)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport)

set(PROJECT_SOURCES resourses.qrc view/main.cpp view/mainwindow.cpp view/mainwindow.h view/mainwindow.ui model/model.h model/model.cc model/token.h controller/controller.h view/qcustomplot.cpp view/qcustomplot.h img/background.png)

set(QT_PREFIXED_MODULES ${QT_MODULES})
list(TRANSFORM QT_PREFIXED_MODULES PREPEND "Qt6::")

# Building
add_executable(calc ${PROJECT_SOURCES})

target_link_libraries(calc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport)
target_include_directories(calc PRIVATE view)
