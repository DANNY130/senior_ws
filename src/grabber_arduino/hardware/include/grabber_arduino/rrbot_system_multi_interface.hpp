// Copyright 2021 Department of Engineering Cybernetics, NTNU
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ROS2_CONTROL_DEMO_EXAMPLE_3__RRBOT_SYSTEM_MULTI_INTERFACE_HPP_
#define ROS2_CONTROL_DEMO_EXAMPLE_3__RRBOT_SYSTEM_MULTI_INTERFACE_HPP_

#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "hardware_interface/handle.hpp"
#include "hardware_interface/hardware_info.hpp"
#include "hardware_interface/system_interface.hpp"
#include "hardware_interface/types/hardware_interface_return_values.hpp"
#include "rclcpp/clock.hpp"
#include "rclcpp/duration.hpp"
#include "rclcpp/macros.hpp"
#include "rclcpp/time.hpp"
#include "rclcpp_lifecycle/node_interfaces/lifecycle_node_interface.hpp"
#include "rclcpp_lifecycle/state.hpp"

#include "grabber_arduino/arduino_comms.hpp"
#include "grabber_arduino/visibility_control.h"
#include "grabber_arduino/grabber.hpp"
#include "grabber_arduino/extender.hpp"

namespace ros2_control_demo_example_3
{
class RRBotSystemMultiInterfaceHardware : public hardware_interface::SystemInterface
{


struct Config
{
  std::string extender_name = "";
  std::string grabber_left_name = "";
  std::string grabber_right_name = "";
  float loop_rate = 0.0;
  std::string device = "";
  int baud_rate = 0;
  int timeout_ms = 0;
  int force_sensor = 0;
};;


public:
  RCLCPP_SHARED_PTR_DEFINITIONS(RRBotSystemMultiInterfaceHardware);

  GRABBER_ARDUINO_PUBLIC
  hardware_interface::CallbackReturn on_init(
    const hardware_interface::HardwareInfo & info) override;

  GRABBER_ARDUINO_PUBLIC
  hardware_interface::CallbackReturn on_configure(
    const rclcpp_lifecycle::State & previous_state) override;

  GRABBER_ARDUINO_PUBLIC
  hardware_interface::return_type prepare_command_mode_switch(
    const std::vector<std::string> & start_interfaces,
    const std::vector<std::string> & stop_interfaces) override;

  GRABBER_ARDUINO_PUBLIC
  hardware_interface::CallbackReturn on_activate(
    const rclcpp_lifecycle::State & previous_state) override;

  GRABBER_ARDUINO_PUBLIC
  hardware_interface::CallbackReturn on_deactivate(
    const rclcpp_lifecycle::State & previous_state) override;

  GRABBER_ARDUINO_PUBLIC
  hardware_interface::return_type read(
    const rclcpp::Time & time, const rclcpp::Duration & period) override
  {
    // Update joint states for grabbers and extender
    grabber_left_.update_state(comms_.read_grabber_position(cfg_.grabber_left_name));
    grabber_right_.update_state(comms_.read_grabber_position(cfg_.grabber_right_name));
    extender_.update_state(comms_.read_extender_position(cfg_.extender_name));

    // ...existing code...
  }

  GRABBER_ARDUINO_PUBLIC
  hardware_interface::return_type write(
    const rclcpp::Time & time, const rclcpp::Duration & period) override
  {
    // Send commands to grabbers and extender
    comms_.write_grabber_command(cfg_.grabber_left_name, grabber_left_.get_command());
    comms_.write_grabber_command(cfg_.grabber_right_name, grabber_right_.get_command());
    comms_.write_extender_command(cfg_.extender_name, extender_.get_command());

    // ...existing code...
  }

private:
  // Parameters for the RRBot simulation
  ArduinoComms comms_;
  Config cfg_;
  Grabber grabber_left_;
  Grabber grabber_right_;
  Extender extender_;
  
  
};

}  // namespace ros2_control_demo_example_3
#endif  // ROS2_CONTROL_DEMO_EXAMPLE_3__RRBOT_SYSTEM_MULTI_INTERFACE_HPP_
