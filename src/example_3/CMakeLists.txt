cmake_minimum_required(VERSION 3.16)
project(example_3 LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
  add_compile_options(-Wall -Wextra)
endif()

# set the same behavior for windows as it is on linux
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# find dependencies
set(THIS_PACKAGE_INCLUDE_DEPENDS
  hardware_interface
  pluginlib
  rclcpp
  rclcpp_lifecycle
)

# find dependencies
find_package(backward_ros REQUIRED)
find_package(ament_cmake REQUIRED)
foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
  find_package(${Dependency} REQUIRED)
endforeach()

## COMPILE
add_library(
  example_3
  SHARED
  hardware/rrbot_system_multi_interface.cpp
)
target_compile_features(example_3 PUBLIC cxx_std_17)
target_include_directories(example_3 PUBLIC
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/hardware/include>
$<INSTALL_INTERFACE:include/example_3>
)
ament_target_dependencies(
  example_3 PUBLIC
  ${THIS_PACKAGE_INCLUDE_DEPENDS}
)

target_link_libraries(example_3 PUBLIC serial)

# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_features(${PROJECT_NAME} PUBLIC "EXAMPLE_3_BUILDING_DLL")

# Export hardware plugins
pluginlib_export_plugin_description_file(hardware_interface example_3.xml)

# INSTALL
install(
  DIRECTORY hardware/include/
  DESTINATION include/example_3
)
install(
  DIRECTORY description/launch description/ros2_control description/urdf description/rviz
  DESTINATION share/example_3
)
install(
  DIRECTORY bringup/launch bringup/config
  DESTINATION share/example_3
)
install(TARGETS example_3
  EXPORT export_example_3
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)

  ament_add_pytest_test(example_3_urdf_xacro test/test_urdf_xacro.py)
  ament_add_pytest_test(view_example_3_launch test/test_view_robot_launch.py)
  ament_add_pytest_test(run_example_3_launch test/test_rrbot_system_multi_interface_launch.py)
endif()

## EXPORTS
ament_export_targets(export_example_3 HAS_LIBRARY_TARGET)
ament_export_dependencies(${THIS_PACKAGE_INCLUDE_DEPENDS})
ament_package()
