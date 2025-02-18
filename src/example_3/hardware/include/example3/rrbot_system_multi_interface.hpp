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

#ifndef EXAMPLE_3__RRBOT_SYSTEM_MULTI_INTERFACE_HPP_
#define EXAMPLE_3__RRBOT_SYSTEM_MULTI_INTERFACE_HPP_

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
#include "example3/visibility_control.h"

#include "example3/arduino_comms.hpp"
#include "example3/extender.hpp"

namespace example_3
{
class RRBotSystemMultiInterfaceHardware : public hardware_interface::SystemInterface
{
  struct Config
  {
    std::string extender_name = "";
    // std::string grabber_left_name = "";
    // std::string grabber_right_name = "";
    float loop_rate = 0.0;
    std::string device = "";
    int baud_rate = 0;
    int timeout_ms = 0;
    // int force_sensor = 0;
    int enc_counts_per_rev = 0;
    int pid_p = 0;
    int pid_d = 0;
    int pid_i = 0;
    int pid_o = 0;
  };
  
public:
  EXAMPLE_3_PUBLIC
  RCLCPP_SHARED_PTR_DEFINITIONS(RRBotSystemMultiInterfaceHardware);

  EXAMPLE_3_PUBLIC
  hardware_interface::CallbackReturn on_init(
    const hardware_interface::HardwareInfo & info) override;

  EXAMPLE_3_PUBLIC
  std::vector<hardware_interface::StateInterface> export_state_interfaces() override;

  EXAMPLE_3_PUBLIC
  std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;

  EXAMPLE_3_PUBLIC
  hardware_interface::CallbackReturn on_configure(
    const rclcpp_lifecycle::State & previous_state) override;

  EXAMPLE_3_PUBLIC
  hardware_interface::CallbackReturn on_cleanup(
    const rclcpp_lifecycle::State & previous_state) override;

  EXAMPLE_3_PUBLIC
  hardware_interface::CallbackReturn on_activate(
    const rclcpp_lifecycle::State & previous_state) override;

  EXAMPLE_3_PUBLIC
  hardware_interface::CallbackReturn on_deactivate(
    const rclcpp_lifecycle::State & previous_state) override;

  EXAMPLE_3_PUBLIC
  hardware_interface::return_type read(
    const rclcpp::Time & time, const rclcpp::Duration & period) override;

  EXAMPLE_3_PUBLIC
  hardware_interface::return_type write(
    const rclcpp::Time & time, const rclcpp::Duration & period) override;

private:
  // Parameters for the RRBot simulation
  ArduinoComms comms_;
  Config cfg_;
  Extender extender_;
  // Motor grabber_left_;
  // Motor grabber_right_;
};

}  // namespace example_3
#endif  // EXAMPLE_3__RRBOT_SYSTEM_MULTI_INTERFACE_HPP_
