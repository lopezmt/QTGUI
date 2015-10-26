cmake_minimum_required(VERSION 2.8.10)

project(QtToCppXML)

find_package( SlicerExecutionModel REQUIRED )
include( ${SlicerExecutionModel_USE_FILE} )
include(${GenerateCLP_USE_FILE})

set(QT_VERSION 5 CACHE STRING "Choose the expected Qt version (4 or 5).")
set_property(CACHE QT_VERSION PROPERTY STRINGS "4" "5")
if(NOT "${QT_VERSION}" STREQUAL "4" AND NOT "${QT_VERSION}" STREQUAL "5")
  set(QT_VERSION 5 CACHE STRING "Choose the expected Qt version (4 or 5)." FORCE)
  message(WARNING "Setting QT_VERSION to '4' as no valid value was specified.")
endif()

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


set( MySources
lgen.cpp
lgen.h
main.cpp
mgen.cpp
mgen.h
parse.h
parse.cpp
sgen.cpp
sgen.h
)

GENERATECLP(MySources QtToCppXML.xml)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${QtToCppXML_BINARY_DIR}/bin)

add_executable( QtToCppXML ${MySources} )
target_link_libraries( QtToCppXML ${QT_LIBRARIES})

# --------------------------------------------------------------------------
# Configure support files
# --------------------------------------------------------------------------  
configure_file(
  QtToCppXML.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/QtToCppXML.cmake
  @ONLY
  )
include(GenerateQtToCppXMLConfig.cmake)
