# Create the fooCLP.h file.  This file should be included in
# foo.cxx and the PARSE_ARGS pre-processor macro used to process command line
# arguments.
#
# Usage: QtToCppXML(foo_SRCS UI_XML_FILE )
#
# foo_SRCS should be a list of source containing foo.cxx.
macro(QtToCppXML)
  set(options
    VERBOSE
  )
  set(oneValueArgs
    SOURCES
    NAME
    UIXML_FILE
  )
  set(multiValueArgs
    PREFIXES
  )
  CMAKE_PARSE_ARGUMENTS(QtToCppXML
  "${options}"
  "${oneValueArgs}"
  "${multiValueArgs}"
  ${ARGN}
  )
  if( QtToCppXML_VERBOSE )
    message("SOURCE Variable: ${QtToCppXML_SOURCES} ")
    message("NAME: ${QtToCppXML_NAME} ")
    message("UIXML File: ${QtToCppXML_UIXML_FILE}")
    message("PREFIXES: ${QtToCppXML_PREFIXES}")
  endif()
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

  if(IS_ABSOLUTE ${QtToCppXML_UIXML_FILE} )
    set(UIXML_FILE_PATH ${QtToCppXML_UIXML_FILE})
  else()
    set(UIXML_FILE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${QtToCppXML_UIXML_FILE})
  endif()

  set(ModelSuffix Model)
  set(LoadSuffix Load)
  set(SaveSuffix Save)
  if( QtToCppXML_PREFIXES )
    if( QtToCppXML_VERBOSE )
      message( WARNING "There are prefixes!" )
    endif()
    set( PREFIXES_ARGS "${quote}-x " )
    foreach( prefix ${QtToCppXML_PREFIXES} )
      set( PREFIXES_ARGS "${PREFIXES_ARGS}${prefix}," )
    endforeach()
    set( PREFIXES_ARGS "${PREFIXES_ARGS}${quote}" )
  endif()
  foreach( suffix ${ModelSuffix} ${LoadSuffix} ${SaveSuffix})
    foreach( extensions ".h" ".cpp" )
      if( QtToCppXML_PREFIXES )
        foreach( prefix ${QtToCppXML_PREFIXES} )
          list(APPEND listOutputFiles ${CMAKE_CURRENT_BINARY_DIR}/${prefix}${suffix}_${QtToCppXML_NAME}${extensions})
        endforeach()
      else()
        list(APPEND listOutputFiles ${CMAKE_CURRENT_BINARY_DIR}/${suffix}_${QtToCppXML_NAME}${extensions})
      endif()
    endforeach()
  endforeach()
  if( QtToCppXML_VERBOSE )
    message( "List output files: ${listOutputFiles}" )
  endif()
  add_custom_command(
      OUTPUT ${listOutputFiles}
      DEPENDS "${QtToCppXML_EXE}" "${UIXML_FILE}"
      COMMAND "${QtToCppXML_EXE}"
      -u "${quote}${UIXML_FILE_PATH}${quote}"
      -d "${quote}${CMAKE_CURRENT_BINARY_DIR}${quote}"
      -l "${quote}${LoadSuffix}_${QtToCppXML_NAME}${quote}"
      -s "${quote}${SaveSuffix}_${QtToCppXML_NAME}${quote}"
      -m "${quote}${ModelSuffix}_${QtToCppXML_NAME}${quote}"
      ${PREFIXES_ARGS}
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
  list( APPEND ${QtToCppXML_SOURCES} ${output} )
  endforeach()
  include_directories(${CMAKE_CURRENT_BINARY_DIR})
  
endmacro(QtToCppXML)
