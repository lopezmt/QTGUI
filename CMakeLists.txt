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
  find_package(Qt5 COMPONENTS Widgets)
  include_directories(${Qt5Widgets_INCLUDE_DIRS})
  add_definitions(${Qt5Widgets_DEFINITIONS})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
  set(QT_LIBRARIES ${Qt5Widgets_LIBRARIES})
else()
  message(FATAL_ERROR "Requires Qt version '4' or '5'.")
endif()


set( MySources
lgen.cpp
lgen.h
mgen.cpp
mgen.h
parse.h
parse.cpp
sgen.cpp
sgen.h
)

if(UNIX)
  SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

SEMMacroBuildCLI(
    NAME QtToCppXML
    EXECUTABLE_ONLY
    ADDITIONAL_SRCS ${MySources}
    TARGET_LIBRARIES ${QT_LIBRARIES}
    INCLUDE_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${QtToCppXML_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${QtToCppXML_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${QtToCppXML_BINARY_DIR}/bin
    INSTALL_ARCHIVE_DESTINATION lib
    INSTALL_LIBRARY_DESTINATION lib
    INSTALL_RUNTIME_DESTINATION bin
    )

# --------------------------------------------------------------------------
# Configure support files
# --------------------------------------------------------------------------  
configure_file(
  ${QtToCppXML_SOURCE_DIR}/QtToCppXML.cmake
  ${PROJECT_BINARY_DIR}/QtToCppXML.cmake
  @ONLY
  )

configure_file(${QtToCppXML_SOURCE_DIR}/UseQtToCppXML.cmake.in
  ${PROJECT_BINARY_DIR}/UseQtToCppXML.cmake
  @ONLY)

set(QtToCppXML_CMAKE_DIR_CONFIG ${PROJECT_BINARY_DIR})
set(QMAKE_CONFIG ${QT_QMAKE_EXECUTABLE})
configure_file(${QtToCppXML_SOURCE_DIR}/QtToCppXMLConfig.cmake.in
  ${PROJECT_BINARY_DIR}/QtToCppXMLConfig.cmake @ONLY)


if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/QtToCppXML)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")

install(FILES
  "${PROJECT_BINARY_DIR}/QtToCppXML.cmake"  
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

install(FILES
  "${PROJECT_BINARY_DIR}/QtToCppXMLConfig.cmake"  
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

install(FILES
  "${PROJECT_BINARY_DIR}/UseQtToCppXML.cmake"  
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)
