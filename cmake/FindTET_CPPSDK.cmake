# Finds CPPSDK headers and libraries
#
# Usage of this module as follows:
#
#     find_package( TET_CPPSDK )
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
#  TET_CPPSDK_ROOT_DIR  Set this variable to the root installation of
#                     EyeTribe if the module has problems finding 
#                     the proper installation path.
#
# Variables defined by this module:
#
#  TET_CPPSDK_FOUND               - have the eyetribe libs been found
#  TET_CPPSDK_LIBRARIES           - path to the eyetribe library (currently, only contains CalibrationLib)
#  TET_CPPSDK_INCLUDE_DIRS        - path to where the EyeTribe modules have been found

FIND_PATH(TET_CPPSDK_ROOT_DIR
  NAMES include/gazeapi.h
  HINTS ${CppSamples_SOURCE_DIR}/../SDK/
)

FIND_PATH(TET_CPPSDK_INCLUDE_DIR
  NAMES gazeapi.h
  HINTS ${TET_CPPSDK_ROOT_DIR}/include
)
  
FIND_LIBRARY(TET_CPPSDK_GAZEAPI_LIB
  NAMES GazeApiLib libGazeApiLib
  HINTS ${TET_CPPSDK_ROOT_DIR}/lib
)

IF( WIN32 )
  FIND_LIBRARY(TET_CPPSDK_DEBUG_GAZEAPI_LIB
	NAMES GazeApiLibD libGazeApiLibD
	HINTS ${TET_CPPSDK_ROOT_DIR}/lib
  )
  SET( TET_CPPSDK_GAZEAPI_LIB  "optimized" "${TET_CPPSDK_GAZEAPI_LIB}" )
  SET( TET_CPPSDK_GAZEAPI_LIB  "${TET_CPPSDK_GAZEAPI_LIB}" "debug" "${TET_CPPSDK_DEBUG_GAZEAPI_LIB}" )
ENDIF()

##
# Check that the just (above) defined variables are valid paths:
#  - EYETRIBE_LIBRARIES
#  - EYETRIBE_INCLUDE_DIRS
# In that case, EYETRIBE_FOUND is set to True.
INCLUDE( FindPackageHandleStandardArgs )
find_package_handle_standard_args( TET_CPPSDK DEFAULT_MSG TET_CPPSDK_GAZEAPI_LIB TET_CPPSDK_INCLUDE_DIR )

IF( TET_CPPSDK_FOUND )
  SET( TET_CPPSDK_INCLUDE_DIRS "${TET_CPPSDK_INCLUDE_DIR}" )
  SET( TET_CPPSDK_LIBS "${TET_CPPSDK_GAZEAPI_LIB}" )
  mark_as_advanced( TET_CPPSDK_ROOT_DIR TET_CPPSDK_FOUND TET_CPPSDK_LIBS TET_CPPSDK_INCLUDE_DIRS TET_CPPSDK_GAZEAPI_LIB)
  message (STATUS "Found the following C++SDK library:" )
  message (STATUS "${TET_CPPSDK_LIBS}")
ELSE()
  message (FATAL_ERROR "Could not find the C++SDK library!")
ENDIF()
