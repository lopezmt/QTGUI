cmake_minimum_required(VERSION 2.8.10)

set(MyProjectName QTGUIExample)

project(MyProjectName)

find_package(QtToCppXML REQUIRED)
include(${QtToCppXML_USE_FILE})

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set( MySources
main.cpp
mainwindow.cpp
)

include_directories( ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} )

QT4_WRAP_CPP(QtProject_HEADERS_MOC mainwindow.h)
QT4_WRAP_UI(UI_FILES mainwindow.ui)

list( APPEND
MySources
${QtProject_HEADERS_MOC}
${UI_FILES}
)


QtToCppXML( MySources ${MyProjectName} mainwindow.ui )

add_executable( QTGUIExample ${MySources} )
target_link_libraries( QTGUIExample ${QT_LIBRARIES})
