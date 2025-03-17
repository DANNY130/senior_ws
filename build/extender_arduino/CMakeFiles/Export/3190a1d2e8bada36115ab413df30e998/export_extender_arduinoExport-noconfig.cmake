#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "extender_arduino::extender_arduino" for configuration ""
set_property(TARGET extender_arduino::extender_arduino APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(extender_arduino::extender_arduino PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libextender_arduino.so"
  IMPORTED_SONAME_NOCONFIG "libextender_arduino.so"
  )

list(APPEND _cmake_import_check_targets extender_arduino::extender_arduino )
list(APPEND _cmake_import_check_files_for_extender_arduino::extender_arduino "${_IMPORT_PREFIX}/lib/libextender_arduino.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
