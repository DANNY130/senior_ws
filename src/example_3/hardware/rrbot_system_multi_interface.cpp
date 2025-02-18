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

#include "example_3/rrbot_system_multi_interface.hpp"

#include <chrono>
#include <cmath>
#include <iomanip>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include "rclcpp/rclcpp.hpp"

namespace example_3
{
hardware_interface::CallbackReturn RRBotSystemMultiInterfaceHardware::on_init(
  const hardware_interface::HardwareInfo & info)
{
  if (
    hardware_interface::SystemInterface::on_init(info) !=
    hardware_interface::CallbackReturn::SUCCESS)
  {
    return hardware_interface::CallbackReturn::ERROR;
    }
  
    return hardware_interface::CallbackReturn::SUCCESS;
  }

  cfg_.extender_name = info_.hardware_parameters["extender_name"];
  // cfg_.grabber_left_name = info_.hardware_parameters["grabber_left_name"];
  // cfg_.grabber_right_name = info_.hardware_parameters["grabber_right_name"];
  cfg_.loop_rate = std::stof(info_.hardware_parameters["loop_rate"]);
  cfg_.device = info_.hardware_parameters["device"];
  cfg_.baud_rate = std::stoi(info_.hardware_parameters["baud_rate"]);
  cfg_.timeout_ms = std::stoi(info_.hardware_parameters["timeout_ms"]);
  // cfg_.force_sensor = std::stoi(info_.hardware_parameters["force_sensor"]);
  cfg_.enc_counts_per_rev = std::stoi(info_.hardware_parameters["enc_counts_per_rev"]);
  if (info_.hardware_parameters.count("pid_p") > 0)
  {
    cfg_.pid_p = std::stoi(info_.hardware_parameters["pid_p"]);
    cfg_.pid_d = std::stoi(info_.hardware_parameters["pid_d"]);
    cfg_.pid_i = std::stoi(info_.hardware_parameters["pid_i"]);
    cfg_.pid_o = std::stoi(info_.hardware_parameters["pid_o"]);
  }
  else
  {
    RCLCPP_INFO(rclcpp::get_logger("RRBotSystemMultiInterfaceHardware"), "PID values not supplied, using defaults.");
  }

  // Initialize the extender
  extender_.setup(cfg_.extender_name, cfg_.enc_counts_per_rev);
  

  for (const hardware_interface::ComponentInfo & joint : info_.joints)
  {
    // RRBotSystemMultiInterface has exactly 3 state interfaces
    // and 3 command interfaces on each joint
    if (joint.command_interfaces.size() != 1)
    {
      RCLCPP_FATAL(
        get_logger("RRBotSystemMultiInterfaceHardware"), "Joint '%s' has %zu command interfaces. 1 expected.", joint.name.c_str(),
        joint.command_interfaces.size());
      return hardware_interface::CallbackReturn::ERROR;
        }

        if (joint.command_interfaces[0].name != hardware_interface::HW_IF_VELOCITY)
        {
      RCLCPP_FATAL(
        get_logger("RRBotSystemMultiInterfaceHardware"), "Joint '%s' has %s command interface. Expected %s.",
        joint.name.c_str(), joint.command_interfaces[0].name.c_str(),
        hardware_interface::HW_IF_VELOCITY);
      return hardware_interface::CallbackReturn::ERROR;
    }

    if (joint.state_interfaces.size() != 2)
    {
      RCLCPP_FATAL(
        get_logger("RRBotSystemMultiInterfaceHardware"), "Joint '%s'has %zu state interfaces. 2 expected.", joint.name.c_str(),
        joint.command_interfaces.size());
      return hardware_interface::CallbackReturn::ERROR;
        }

        if (joint.state_interfaces[0].name != hardware_interface::HW_IF_POSITION)
        {
      RCLCPP_FATAL(
        get_logger(), "Joint '%s' has %s state interface. Expected %s.",
        joint.name.c_str(), joint.state_interfaces[0].name.c_str(),
        hardware_interface::HW_IF_POSITION);
      return hardware_interface::CallbackReturn::ERROR;
    }

    if (joint.state_interfaces[1].name != hardware_interface::HW_IF_VELOCITY)
    {
      RCLCPP_FATAL(
        get_logger(), "Joint '%s' has %s state interface. Expected %s.",
        joint.name.c_str(), joint.state_interfaces[1].name.c_str(),
        hardware_interface::HW_IF_VELOCITY);
      return hardware_interface::CallbackReturn::ERROR;
  }

  return hardware_interface::CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::StateInterface> RRBotSystemMultiInterfaceHardware::export_state_interfaces()
{
  std::vector<hardware_interface::StateInterface> state_interfaces;

  state_interfaces.emplace_back(hardware_interface::StateInterface(
    extender_.name, hardware_interface::HW_IF_POSITION, &extender_.pos));
  state_interfaces.emplace_back(hardware_interface::StateInterface(
    extender_.name, hardware_interface::HW_IF_VELOCITY, &extender_.vel));

  return state_interfaces;
}

std::vector<hardware_interface::CommandInterface> RRBotSystemMultiInterfaceHardware::export_command_interfaces()
{
  std::vector<hardware_interface::CommandInterface> command_interfaces;

  command_interfaces.emplace_back(hardware_interface::CommandInterface(
    extender_.name, hardware_interface::HW_IF_VELOCITY, &extender_.cmd));

  return command_interfaces;
}

hardware_interface::CallbackReturn RRBotSystemMultiInterfaceHardware::on_configure(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  // BEGIN: This part here is for exemplary purposes - Please do not copy to your production code
  RCLCPP_INFO(get_logger("RRBotSystemMultiInterfaceHardware"), "Configuring ...please wait...");

  if (comms_.connected())
  {
    comms_.disconnect();
  }

  comms_.setup(cfg_.device, cfg_.baud_rate, cfg_.timeout_ms);
  
  RCLCPP_INFO(get_logger("RRBotSystemMultiInterfaceHardware"), "Successfully configured!");

  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn RRBotSystemMultiInterfaceHardware::on_cleanup(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(get_logger("RRBotSystemMultiInterfaceHardware"), "Cleaning up ...please wait...");

  if (comms_.connected())
  {
    comms_.disconnect();
  }

  RCLCPP_INFO(get_logger("RRBotSystemMultiInterfaceHardware"), "Successfully cleaned up!");

  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn RRBotSystemMultiInterfaceHardware::on_activate(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  // BEGIN: This part here is for exemplary purposes - Please do not copy to your production code
  RCLCPP_INFO(get_logger("RRBotSystemMultiInterfaceHardware"), "Activating... please wait...");

  if (!comms_.connected())
  {
    return hardware_interface::CallbackReturn::ERROR;
  }

  if (cfg_.pid_p > 0)
  {
    comms_.set_pid_values(cfg_.pid_p, cfg_.pid_d, cfg_.pid_i, cfg_.pid_o);
  }

  RCLCPP_INFO(get_logger("RRBotSystemMultiInterfaceHardware"), "Successfully deactivated!");
  // END: This part here is for exemplary purposes - Please do not copy to your production code

  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn RRBotSystemMultiInterfaceHardware::on_deactivate(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  // BEGIN: This part here is for exemplary purposes - Please do not copy to your production code
  RCLCPP_INFO(get_logger("RRBotSystemMultiInterfaceHardware"), "Deactivating ...please wait...");

  RCLCPP_INFO(get_logger("RRBotSystemMultiInterfaceHardware"), "Successfully deactivated!");
  // END: This part here is for exemplary purposes - Please do not copy to your production code

  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::return_type RRBotSystemMultiInterfaceHardware::read(
  const rclcpp::Time & /*time*/, const rclcpp::Duration & period)
{
  if (!comms_.connected())
  {
    return hardware_interface::return_type::ERROR;
  }

  coms_.read_encoder_values(extender_.enc);

  double delta_time = period.seconds();

  double pos_prev = extender_.pos;
  extender_.pos = extender_.position();
  extender_.vel = (extender_.pos - pos_prev) / delta_time;

  return hardware_interface::return_type::OK;
}

hardware_interface::return_type RRBotSystemMultiInterfaceHardware::write(
  const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/)
{
  if (!comms_.connected())
  {
    return hardware_interface::return_type::ERROR;
  }

  int motor_extender_counts_per_loop = extender_.cmd / extender_.rads_per_count / cfg_.loop_rate;
  comms_.set_motor_values(motor_extender_counts_per_loop);

  return hardware_interface::return_type::OK;
}

}  // namespace example_3

#include "pluginlib/class_list_macros.hpp"

PLUGINLIB_EXPORT_CLASS(
  example_3::RRBotSystemMultiInterfaceHardware,
  hardware_interface::SystemInterface)
