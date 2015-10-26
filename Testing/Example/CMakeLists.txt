cmake_minimum_required(VERSION 2.8.10)

set(MyProjectName QTGUIExample)

project(MyProjectName)

find_package(QtToCppXML REQUIRED)
include(${QtToCppXML_USE_FILE})

set( MySources
main.cpp
mainwindow.cpp
)

include_directories( ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} )

if( QT_VERSION STREQUAL "4" )
  find_package(Qt4 REQUIRED)
  include(${QT_USE_FILE})
  QT4_WRAP_CPP(QtProject_HEADERS_MOC mainwindow.h)
  QT4_WRAP_UI(UI_FILES mainwindow.ui)
  unset(Qt5Widgets_DIR CACHE)
elseif(QT_VERSION STREQUAL "5" )
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTOUIC ON)
  find_package(Qt5Widgets REQUIRED)
  include_directories(${Qt5Widgets_INCLUDE_DIRS})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
  set(QT_LIBRARIES ${Qt5Widgets_LIBRARIES})
else()
  message(FATAL_ERROR "Requires Qt version '4' or '5'.")
endif()

list( APPEND
MySources
${QtProject_HEADERS_MOC}
${UI_FILES}
)

QtToCppXML( SOURCES MySources NAME ${MyProjectName} UIXML_FILE mainwindow.ui VERBOSE)

add_executable( QTGUIExample ${MySources} )
target_link_libraries( QTGUIExample ${QT_LIBRARIES})
