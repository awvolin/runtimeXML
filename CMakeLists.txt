cmake_minimum_required(VERSION 3.5)

project(runtimeXML VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
)

# replace this with the path to your libQt5UiTools.a
set(Qt5UiTools_DIR "/home/alexvolin/Qt/5.15.2/gcc_64/lib/")
find_library(Qt5UiTools_LIBRARIES
             NAMES Qt5UiTools
             HINTS "${Qt5UiTools_DIR}"
             PATH_SUFFIXES lib)

include_directories("${Qt5UiTools_DIR}/../include/QtUiTools") # adjust this path as necessary

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(runtimeXML
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(runtimeXML SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(runtimeXML
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(runtimeXML PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${Qt5UiTools_LIBRARIES})

set_target_properties(runtimeXML PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS runtimeXML
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(runtimeXML)
endif()
