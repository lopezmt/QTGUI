# Generate the QtToCppXMLConfig.cmake file in the build tree and configure
# one the installation tree.

# Settings specific to build trees
#
#
set(QtToCppXML_USE_FILE_CONFIG ${QtToCppXML_BINARY_DIR}/UseQtToCppXML.cmake)
configure_file(${QtToCppXML_SOURCE_DIR}/UseQtToCppXML.cmake.in
  ${QtToCppXML_USE_FILE_CONFIG}
  @ONLY)

set(QtToCppXML_INCLUDE_DIRS_CONFIG ${QtToCppXML_SOURCE_DIR})

set(QtToCppXML_CMAKE_DIR_CONFIG ${QtToCppXML_BINARY_DIR})
set(QtToCppXML_CONFIG_DIR "${QtToCppXML_BINARY_DIR}")
set(QMAKE_CONFIG ${QT_QMAKE_EXECUTABLE})
configure_file(${QtToCppXML_SOURCE_DIR}/QtToCppXMLConfig.cmake.in
  ${QtToCppXML_BINARY_DIR}/QtToCppXMLConfig.cmake @ONLY)

