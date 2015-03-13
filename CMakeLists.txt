cmake_minimum_required(VERSION 2.8.10)

project(QtToCppXML)

find_package( SlicerExecutionModel REQUIRED )
include( ${SlicerExecutionModel_USE_FILE} )
include(${GenerateCLP_USE_FILE})

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

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

add_executable( QtToCppXML ${MySources} )
target_link_libraries( QtToCppXML ${QT_LIBRARIES})
