# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/olympusolutions/senior_ws/src/extender_arduino

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/olympusolutions/senior_ws/build/extender_arduino

# Include any dependencies generated for this target.
include CMakeFiles/extender_arduino.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/extender_arduino.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/extender_arduino.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/extender_arduino.dir/flags.make

CMakeFiles/extender_arduino.dir/hardware/diffbot_system.cpp.o: CMakeFiles/extender_arduino.dir/flags.make
CMakeFiles/extender_arduino.dir/hardware/diffbot_system.cpp.o: /home/olympusolutions/senior_ws/src/extender_arduino/hardware/diffbot_system.cpp
CMakeFiles/extender_arduino.dir/hardware/diffbot_system.cpp.o: CMakeFiles/extender_arduino.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/olympusolutions/senior_ws/build/extender_arduino/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/extender_arduino.dir/hardware/diffbot_system.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/extender_arduino.dir/hardware/diffbot_system.cpp.o -MF CMakeFiles/extender_arduino.dir/hardware/diffbot_system.cpp.o.d -o CMakeFiles/extender_arduino.dir/hardware/diffbot_system.cpp.o -c /home/olympusolutions/senior_ws/src/extender_arduino/hardware/diffbot_system.cpp

CMakeFiles/extender_arduino.dir/hardware/diffbot_system.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/extender_arduino.dir/hardware/diffbot_system.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/olympusolutions/senior_ws/src/extender_arduino/hardware/diffbot_system.cpp > CMakeFiles/extender_arduino.dir/hardware/diffbot_system.cpp.i

CMakeFiles/extender_arduino.dir/hardware/diffbot_system.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/extender_arduino.dir/hardware/diffbot_system.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/olympusolutions/senior_ws/src/extender_arduino/hardware/diffbot_system.cpp -o CMakeFiles/extender_arduino.dir/hardware/diffbot_system.cpp.s

# Object files for target extender_arduino
extender_arduino_OBJECTS = \
"CMakeFiles/extender_arduino.dir/hardware/diffbot_system.cpp.o"

# External object files for target extender_arduino
extender_arduino_EXTERNAL_OBJECTS =

libextender_arduino.so: CMakeFiles/extender_arduino.dir/hardware/diffbot_system.cpp.o
libextender_arduino.so: CMakeFiles/extender_arduino.dir/build.make
libextender_arduino.so: /opt/ros/jazzy/lib/libmock_components.so
libextender_arduino.so: /opt/ros/jazzy/lib/libhardware_interface.so
libextender_arduino.so: /opt/ros/jazzy/lib/libcontrol_msgs__rosidl_typesupport_fastrtps_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libcontrol_msgs__rosidl_typesupport_fastrtps_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libcontrol_msgs__rosidl_typesupport_introspection_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libcontrol_msgs__rosidl_typesupport_introspection_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libcontrol_msgs__rosidl_typesupport_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libcontrol_msgs__rosidl_generator_py.so
libextender_arduino.so: /opt/ros/jazzy/lib/libcontrol_msgs__rosidl_typesupport_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libcontrol_msgs__rosidl_generator_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libsensor_msgs__rosidl_typesupport_fastrtps_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libsensor_msgs__rosidl_typesupport_fastrtps_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libsensor_msgs__rosidl_typesupport_introspection_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libsensor_msgs__rosidl_typesupport_introspection_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libsensor_msgs__rosidl_typesupport_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libsensor_msgs__rosidl_typesupport_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libsensor_msgs__rosidl_generator_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libjoint_limiter_interface.so
libextender_arduino.so: /opt/ros/jazzy/lib/libjoint_saturation_limiter.so
libextender_arduino.so: /opt/ros/jazzy/lib/libjoint_limits_helpers.so
libextender_arduino.so: /opt/ros/jazzy/lib/libclass_loader.so
libextender_arduino.so: /opt/ros/jazzy/lib/librclcpp_lifecycle.so
libextender_arduino.so: /opt/ros/jazzy/lib/librcl_lifecycle.so
libextender_arduino.so: /opt/ros/jazzy/lib/liblifecycle_msgs__rosidl_typesupport_fastrtps_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/liblifecycle_msgs__rosidl_typesupport_introspection_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/liblifecycle_msgs__rosidl_typesupport_fastrtps_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/liblifecycle_msgs__rosidl_typesupport_introspection_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/liblifecycle_msgs__rosidl_typesupport_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/liblifecycle_msgs__rosidl_generator_py.so
libextender_arduino.so: /opt/ros/jazzy/lib/liblifecycle_msgs__rosidl_typesupport_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/liblifecycle_msgs__rosidl_generator_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/librealtime_tools.so
libextender_arduino.so: /opt/ros/jazzy/lib/libthread_priority.so
libextender_arduino.so: /opt/ros/jazzy/lib/librclcpp_action.so
libextender_arduino.so: /opt/ros/jazzy/lib/librclcpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/liblibstatistics_collector.so
libextender_arduino.so: /opt/ros/jazzy/lib/librosgraph_msgs__rosidl_typesupport_fastrtps_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/librosgraph_msgs__rosidl_typesupport_fastrtps_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/librosgraph_msgs__rosidl_typesupport_introspection_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/librosgraph_msgs__rosidl_typesupport_introspection_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/librosgraph_msgs__rosidl_typesupport_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/librosgraph_msgs__rosidl_generator_py.so
libextender_arduino.so: /opt/ros/jazzy/lib/librosgraph_msgs__rosidl_typesupport_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/librosgraph_msgs__rosidl_generator_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libstatistics_msgs__rosidl_typesupport_fastrtps_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libstatistics_msgs__rosidl_typesupport_fastrtps_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libstatistics_msgs__rosidl_typesupport_introspection_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libstatistics_msgs__rosidl_typesupport_introspection_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libstatistics_msgs__rosidl_typesupport_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libstatistics_msgs__rosidl_generator_py.so
libextender_arduino.so: /opt/ros/jazzy/lib/libstatistics_msgs__rosidl_typesupport_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libstatistics_msgs__rosidl_generator_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/librcl_action.so
libextender_arduino.so: /opt/ros/jazzy/lib/librcl.so
libextender_arduino.so: /opt/ros/jazzy/lib/librcl_interfaces__rosidl_typesupport_fastrtps_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/librcl_interfaces__rosidl_typesupport_introspection_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/librcl_interfaces__rosidl_typesupport_fastrtps_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/librcl_interfaces__rosidl_typesupport_introspection_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/librcl_interfaces__rosidl_typesupport_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/librcl_interfaces__rosidl_generator_py.so
libextender_arduino.so: /opt/ros/jazzy/lib/librcl_interfaces__rosidl_typesupport_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/librcl_interfaces__rosidl_generator_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/librcl_yaml_param_parser.so
libextender_arduino.so: /opt/ros/jazzy/lib/libtracetools.so
libextender_arduino.so: /opt/ros/jazzy/lib/librcl_logging_interface.so
libextender_arduino.so: /opt/ros/jazzy/lib/librmw_implementation.so
libextender_arduino.so: /opt/ros/jazzy/lib/libament_index_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libtype_description_interfaces__rosidl_typesupport_fastrtps_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libtype_description_interfaces__rosidl_typesupport_introspection_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libtype_description_interfaces__rosidl_typesupport_fastrtps_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libtype_description_interfaces__rosidl_typesupport_introspection_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libtype_description_interfaces__rosidl_typesupport_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libtype_description_interfaces__rosidl_generator_py.so
libextender_arduino.so: /opt/ros/jazzy/lib/libtype_description_interfaces__rosidl_typesupport_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libtype_description_interfaces__rosidl_generator_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libaction_msgs__rosidl_typesupport_fastrtps_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libaction_msgs__rosidl_typesupport_fastrtps_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libaction_msgs__rosidl_typesupport_introspection_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libaction_msgs__rosidl_typesupport_introspection_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libaction_msgs__rosidl_typesupport_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libaction_msgs__rosidl_generator_py.so
libextender_arduino.so: /opt/ros/jazzy/lib/libunique_identifier_msgs__rosidl_typesupport_fastrtps_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libservice_msgs__rosidl_typesupport_fastrtps_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libunique_identifier_msgs__rosidl_typesupport_fastrtps_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libservice_msgs__rosidl_typesupport_fastrtps_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libunique_identifier_msgs__rosidl_typesupport_introspection_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libservice_msgs__rosidl_typesupport_introspection_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libaction_msgs__rosidl_typesupport_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libaction_msgs__rosidl_generator_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libunique_identifier_msgs__rosidl_typesupport_introspection_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libservice_msgs__rosidl_typesupport_introspection_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libunique_identifier_msgs__rosidl_typesupport_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libservice_msgs__rosidl_typesupport_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libunique_identifier_msgs__rosidl_typesupport_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libunique_identifier_msgs__rosidl_generator_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libservice_msgs__rosidl_typesupport_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libservice_msgs__rosidl_generator_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libtrajectory_msgs__rosidl_typesupport_fastrtps_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libtrajectory_msgs__rosidl_typesupport_fastrtps_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libtrajectory_msgs__rosidl_typesupport_introspection_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libtrajectory_msgs__rosidl_typesupport_introspection_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libtrajectory_msgs__rosidl_typesupport_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libtrajectory_msgs__rosidl_generator_py.so
libextender_arduino.so: /opt/ros/jazzy/lib/libgeometry_msgs__rosidl_typesupport_fastrtps_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libgeometry_msgs__rosidl_typesupport_fastrtps_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libgeometry_msgs__rosidl_typesupport_introspection_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libtrajectory_msgs__rosidl_typesupport_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libtrajectory_msgs__rosidl_generator_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libgeometry_msgs__rosidl_typesupport_introspection_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libgeometry_msgs__rosidl_typesupport_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libstd_msgs__rosidl_typesupport_fastrtps_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libstd_msgs__rosidl_typesupport_fastrtps_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libstd_msgs__rosidl_typesupport_introspection_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libgeometry_msgs__rosidl_typesupport_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libgeometry_msgs__rosidl_generator_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libstd_msgs__rosidl_typesupport_introspection_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libstd_msgs__rosidl_typesupport_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libbuiltin_interfaces__rosidl_typesupport_fastrtps_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/librosidl_typesupport_fastrtps_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libbuiltin_interfaces__rosidl_typesupport_introspection_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libbuiltin_interfaces__rosidl_typesupport_fastrtps_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/librosidl_typesupport_fastrtps_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/librmw.so
libextender_arduino.so: /opt/ros/jazzy/lib/librosidl_dynamic_typesupport.so
libextender_arduino.so: /opt/ros/jazzy/lib/libfastcdr.so.2.2.5
libextender_arduino.so: /opt/ros/jazzy/lib/libbuiltin_interfaces__rosidl_typesupport_introspection_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/librosidl_typesupport_introspection_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/librosidl_typesupport_introspection_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libbuiltin_interfaces__rosidl_typesupport_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/librosidl_typesupport_cpp.so
libextender_arduino.so: /opt/ros/jazzy/lib/libbuiltin_interfaces__rosidl_generator_py.so
libextender_arduino.so: /opt/ros/jazzy/lib/libstd_msgs__rosidl_typesupport_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libbuiltin_interfaces__rosidl_typesupport_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libstd_msgs__rosidl_generator_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/libbuiltin_interfaces__rosidl_generator_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/librosidl_typesupport_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/librcpputils.so
libextender_arduino.so: /opt/ros/jazzy/lib/librosidl_runtime_c.so
libextender_arduino.so: /opt/ros/jazzy/lib/librcutils.so
libextender_arduino.so: /opt/ros/jazzy/lib/liburdf.so
libextender_arduino.so: /opt/ros/jazzy/lib/aarch64-linux-gnu/liburdfdom_model.so.4.0
libextender_arduino.so: /usr/lib/aarch64-linux-gnu/libtinyxml2.so.10.0.0
libextender_arduino.so: /usr/lib/aarch64-linux-gnu/libconsole_bridge.so.1.0
libextender_arduino.so: CMakeFiles/extender_arduino.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/olympusolutions/senior_ws/build/extender_arduino/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libextender_arduino.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/extender_arduino.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/extender_arduino.dir/build: libextender_arduino.so
.PHONY : CMakeFiles/extender_arduino.dir/build

CMakeFiles/extender_arduino.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/extender_arduino.dir/cmake_clean.cmake
.PHONY : CMakeFiles/extender_arduino.dir/clean

CMakeFiles/extender_arduino.dir/depend:
	cd /home/olympusolutions/senior_ws/build/extender_arduino && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/olympusolutions/senior_ws/src/extender_arduino /home/olympusolutions/senior_ws/src/extender_arduino /home/olympusolutions/senior_ws/build/extender_arduino /home/olympusolutions/senior_ws/build/extender_arduino /home/olympusolutions/senior_ws/build/extender_arduino/CMakeFiles/extender_arduino.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/extender_arduino.dir/depend

