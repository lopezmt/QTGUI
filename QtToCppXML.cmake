# Create the fooCLP.h file.  This file should be included in
# foo.cxx and the PARSE_ARGS pre-processor macro used to process command line
# arguments.
#
# Usage: QtToCppXML(foo_SRCS UI_XML_FILE )
#
# foo_SRCS should be a list of source containing foo.cxx.
macro(QtToCppXML SOURCES MY_NAME UIXML_FILE )
  # Sanity checks
  if("${QtToCppXML_EXE}" STREQUAL "")
    message(FATAL_ERROR "QtToCppXML_EXE value is invalid. It shouldn't be an empty string !")
  endif()

  # The shell into which nmake.exe executes the custom command has some issues
  # with mixing quoted and unquoted arguments :( Let's help.

  if(CMAKE_GENERATOR MATCHES "NMake Makefiles")
    set(verbatim "")
    set(quote "\"")
  else()
    set(verbatim "VERBATIM")
    set(quote "")
  endif()

  if(IS_ABSOLUTE ${UIXML_FILE} )
    set(UIXML_FILE_PATH ${UIXML_FILE})
  else()
    set(UIXML_FILE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${UIXML_FILE})
  endif()

  set(ModelSuffix Model)
  set(LoadSuffix Load)
  set(SaveSuffix Save)
  foreach( suffix ${ModelSuffix} ${LoadSuffix} ${SaveSuffix})
    foreach( extensions ".h" ".cpp" )
      list(APPEND listOutputSuffixes ${suffix}${extensions})
    endforeach()
  endforeach()

  foreach( suff ${listOutputSuffixes} )
    list(APPEND listOutputFiles ${CMAKE_CURRENT_BINARY_DIR}/${MY_NAME}${suff} )
  endforeach()
  add_custom_command(
      OUTPUT ${listOutputFiles}
      DEPENDS "${QtToCppXML_EXE}" "${UIXML_FILE}"
      COMMAND "${QtToCppXML_EXE}"
      -u "${quote}${UIXML_FILE_PATH}${quote}"
      -d "${quote}${CMAKE_CURRENT_BINARY_DIR}${quote}"
      -l "${quote}${MY_NAME}${LoadSuffix}${quote}"
      -s "${quote}${MY_NAME}${SaveSuffix}${quote}"
      -m "${quote}${MY_NAME}${ModelSuffix}${quote}"
      ${verbatim}
      )

  foreach(INPUT_SOURCE_FILE ${${SOURCES}} )
    foreach(output ${listOutputFiles} )
      set_source_files_properties(${INPUT_SOURCE_FILE} PROPERTIES
      OBJECT_DEPENDS ${output} )
    endforeach()
  endforeach()

  foreach(output ${listOutputFiles} )
    set_source_files_properties(
      ${output} PROPERTIES GENERATED TRUE )# Mark the file as generated
    get_filename_component(EXT_output ${output} EXT)
    if( ${EXT_output} STREQUAL ".h" )
      set_source_files_properties( ${output} PROPERTIES HEADER_FILE_ONLY TRUE ) # Mark the file as a header file
    endif()
  list( APPEND ${SOURCES} ${output} )
  endforeach()
  include_directories(${CMAKE_CURRENT_BINARY_DIR})
  
endmacro(QtToCppXML)
