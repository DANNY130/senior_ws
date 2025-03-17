# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_extender_arduino_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED extender_arduino_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(extender_arduino_FOUND FALSE)
  elseif(NOT extender_arduino_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(extender_arduino_FOUND FALSE)
  endif()
  return()
endif()
set(_extender_arduino_CONFIG_INCLUDED TRUE)

# output package information
if(NOT extender_arduino_FIND_QUIETLY)
  message(STATUS "Found extender_arduino: 0.0.0 (${extender_arduino_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'extender_arduino' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT extender_arduino_DEPRECATED_QUIET)
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(extender_arduino_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "ament_cmake_export_targets-extras.cmake;ament_cmake_export_dependencies-extras.cmake")
foreach(_extra ${_extras})
  include("${extender_arduino_DIR}/${_extra}")
endforeach()
