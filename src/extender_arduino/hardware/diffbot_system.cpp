// Copyright 2021 ros2_control Development Team
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

#include "extender_arduino/diffbot_system.hpp"

#include <chrono>
#include <cmath>
#include <limits>
#include <memory>
#include <vector>

#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include "rclcpp/rclcpp.hpp"

namespace extender_arduino
{
hardware_interface::CallbackReturn ExtenderArduinoHardware::on_init(
  const hardware_interface::HardwareInfo & info)
{
  if (
    hardware_interface::SystemInterface::on_init(info) !=
    hardware_interface::CallbackReturn::SUCCESS)
  {
    return hardware_interface::CallbackReturn::ERROR;
  }


  cfg_.joint = info_.hardware_parameters["joints"];
  cfg_.platform = info_.hardware_parameters["platform"];
  cfg_.gripper_l = info_.hardware_parameters["gripper_l"];
  cfg_.gripper_r = info_.hardware_parameters["gripper_r"];
  cfg_.loop_rate = std::stof(info_.hardware_parameters["loop_rate"]);
  cfg_.device = info_.hardware_parameters["device"];
  cfg_.baud_rate = std::stoi(info_.hardware_parameters["baud_rate"]);
  cfg_.timeout_ms = std::stoi(info_.hardware_parameters["timeout_ms"]);
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
    RCLCPP_INFO(rclcpp::get_logger("ExtenderArduinoHardware"), "PID values not supplied, using defaults.");
  }
  

  wheel_l_.setup(cfg_.joint, cfg_.enc_counts_per_rev);
  wheel_r_.setup(cfg_.platform, cfg_.enc_counts_per_rev);
  gripper_l_.setup(cfg_.gripper_l);
  gripper_r_.setup(cfg_.gripper_r);

  for (const hardware_interface::ComponentInfo & joint : info_.joints)
  {
    // DiffBotSystem has exactly two states and one command interface on each joint
    if (joint.command_interfaces.size() != 1)
    {
      RCLCPP_FATAL(
        rclcpp::get_logger("ExtenderArduinoHardware"),
        "Joint '%s' has %zu command interfaces found. 1 expected.", joint.name.c_str(),
        joint.command_interfaces.size());
      return hardware_interface::CallbackReturn::ERROR;
    }
    if (joint.name == "slider_left_joint")
    {if (joint.command_interfaces[0].name != hardware_interface::HW_IF_VELOCITY)
    {
      RCLCPP_FATAL(
        rclcpp::get_logger("ExtenderArduinoHardware"),
        "Joint '%s' have %s command interfaces found. '%s' expected.", joint.name.c_str(),
        joint.command_interfaces[0].name.c_str(), hardware_interface::HW_IF_VELOCITY);
      return hardware_interface::CallbackReturn::ERROR;
    }
    }

    else if (joint.name == "gripper_left_joint" || joint.name == "gripper_right_joint")
    {
      if (joint.command_interfaces[0].name != hardware_interface::HW_IF_POSITION)
      {
        RCLCPP_FATAL(
          rclcpp::get_logger("ExtenderArduinoHardware"),
          "Joint '%s' have %s command interfaces found. '%s' expected.", joint.name.c_str(),
          joint.command_interfaces[0].name.c_str(), hardware_interface::HW_IF_POSITION);
        return hardware_interface::CallbackReturn::ERROR;
      }
    }
    else
    {
      RCLCPP_FATAL(
        rclcpp::get_logger("ExtenderArduinoHardware"), "Joint '%s' not found.", joint.name.c_str());
      return hardware_interface::CallbackReturn::ERROR;
    }

    // DiffBotSystem has exactly two states on each joint

    if (joint.state_interfaces.size() != 2)
    {
      RCLCPP_FATAL(
        rclcpp::get_logger("ExtenderArduinoHardware"),
        "Joint '%s' has %zu state interface. 2 expected.", joint.name.c_str(),
        joint.state_interfaces.size());
      return hardware_interface::CallbackReturn::ERROR;
    }

    if (joint.state_interfaces[0].name != hardware_interface::HW_IF_POSITION)
    {
      RCLCPP_FATAL(
        rclcpp::get_logger("ExtenderArduinoHardware"),
        "Joint '%s' have '%s' as first state interface. '%s' expected.", joint.name.c_str(),
        joint.state_interfaces[0].name.c_str(), hardware_interface::HW_IF_POSITION);
      return hardware_interface::CallbackReturn::ERROR;
    }

    if (joint.state_interfaces[1].name != hardware_interface::HW_IF_VELOCITY)
    {
      RCLCPP_FATAL(
        rclcpp::get_logger("ExtenderArduinoHardware"),
        "Joint '%s' have '%s' as second state interface. '%s' expected.", joint.name.c_str(),
        joint.state_interfaces[1].name.c_str(), hardware_interface::HW_IF_VELOCITY);
      return hardware_interface::CallbackReturn::ERROR;
    }
  }

  return hardware_interface::CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::StateInterface> ExtenderArduinoHardware::export_state_interfaces()
{
  std::vector<hardware_interface::StateInterface> state_interfaces;

  state_interfaces.emplace_back(hardware_interface::StateInterface(
    wheel_l_.name, hardware_interface::HW_IF_POSITION, &wheel_l_.pos));
  state_interfaces.emplace_back(hardware_interface::StateInterface(
    wheel_l_.name, hardware_interface::HW_IF_VELOCITY, &wheel_l_.vel));
  
  state_interfaces.emplace_back(hardware_interface::StateInterface(
    wheel_r_.name, hardware_interface::HW_IF_POSITION, &wheel_r_.pos));
  state_interfaces.emplace_back(hardware_interface::StateInterface(
    wheel_r_.name, hardware_interface::HW_IF_VELOCITY, &wheel_r_.vel));
  
  state_interfaces.emplace_back(hardware_interface::StateInterface(
    gripper_l_.name, hardware_interface::HW_IF_POSITION, &gripper_l_.pos));
  state_interfaces.emplace_back(hardware_interface::StateInterface(
    gripper_l_.name, hardware_interface::HW_IF_VELOCITY, &gripper_l_.vel));

  state_interfaces.emplace_back(hardware_interface::StateInterface(
    gripper_r_.name, hardware_interface::HW_IF_POSITION, &gripper_r_.pos));
  state_interfaces.emplace_back(hardware_interface::StateInterface(
    gripper_r_.name, hardware_interface::HW_IF_VELOCITY, &gripper_r_.vel));

  return state_interfaces;
}

std::vector<hardware_interface::CommandInterface> ExtenderArduinoHardware::export_command_interfaces()
{
  std::vector<hardware_interface::CommandInterface> command_interfaces;

  command_interfaces.emplace_back(hardware_interface::CommandInterface(
    wheel_l_.name, hardware_interface::HW_IF_VELOCITY, &wheel_l_.cmd));

  command_interfaces.emplace_back(hardware_interface::CommandInterface(
    wheel_r_.name, hardware_interface::HW_IF_VELOCITY, &wheel_r_.cmd));

  command_interfaces.emplace_back(hardware_interface::CommandInterface(
    gripper_l_.name, hardware_interface::HW_IF_POSITION, &gripper_l_.cmd));

  command_interfaces.emplace_back(hardware_interface::CommandInterface(
    gripper_r_.name, hardware_interface::HW_IF_POSITION, &gripper_r_.cmd));

  return command_interfaces;
}

hardware_interface::CallbackReturn ExtenderArduinoHardware::on_configure(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(rclcpp::get_logger("ExtenderArduinoHardware"), "Configuring ...please wait...");
  if (comms_.connected())
  {
    comms_.disconnect();
  }
  comms_.connect(cfg_.device, cfg_.baud_rate, cfg_.timeout_ms);
  RCLCPP_INFO(rclcpp::get_logger("ExtenderArduinoHardware"), "Successfully configured!");

  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn ExtenderArduinoHardware::on_cleanup(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(rclcpp::get_logger("ExtenderArduinoHardware"), "Cleaning up ...please wait...");
  if (comms_.connected())
  {
    comms_.disconnect();
  }
  RCLCPP_INFO(rclcpp::get_logger("ExtenderArduinoHardware"), "Successfully cleaned up!");

  return hardware_interface::CallbackReturn::SUCCESS;
}


hardware_interface::CallbackReturn ExtenderArduinoHardware::on_activate(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(rclcpp::get_logger("ExtenderArduinoHardware"), "Activating ...please wait...");
  if (!comms_.connected())
  {
    return hardware_interface::CallbackReturn::ERROR;
  }
  if (cfg_.pid_p > 0)
  {
    comms_.set_pid_values(cfg_.pid_p,cfg_.pid_d,cfg_.pid_i,cfg_.pid_o);
  }
  RCLCPP_INFO(rclcpp::get_logger("ExtenderArduinoHardware"), "Successfully activated!");

  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn ExtenderArduinoHardware::on_deactivate(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(rclcpp::get_logger("ExtenderArduinoHardware"), "Deactivating ...please wait...");
  RCLCPP_INFO(rclcpp::get_logger("ExtenderArduinoHardware"), "Successfully deactivated!");

  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::return_type ExtenderArduinoHardware::read(
  const rclcpp::Time & /*time*/, const rclcpp::Duration & period)
{
  if (!comms_.connected())
  {
    return hardware_interface::return_type::ERROR;
  }

  // Read encoder values
  comms_.read_encoder_values(wheel_l_.enc, wheel_l_.enc);
  comms_.read_encoder_values(wheel_r_.enc, wheel_r_.enc);

  double delta_seconds = period.seconds();

  double pos_prev = wheel_l_.pos;
  wheel_l_.pos = wheel_l_.calc_enc_angle();
  wheel_l_.vel = (wheel_l_.pos - pos_prev) / delta_seconds;

  pos_prev = wheel_r_.pos;
  wheel_r_.pos = wheel_r_.calc_enc_angle();
  wheel_r_.vel = (wheel_r_.pos - pos_prev) / delta_seconds;

  // Read servo values
  int gripper_l_degrees_int = static_cast<int>(gripper_l_.degrees);
  int gripper_r_degrees_int = static_cast<int>(gripper_r_.degrees);
  comms_.read_servo_values(gripper_l_degrees_int, gripper_r_degrees_int);
  double pos_prev_l = gripper_l_.pos;
  gripper_l_.pos = gripper_l_.calc_servo_angle();
  gripper_l_.vel = (gripper_l_.pos - pos_prev_l) / delta_seconds;

  double pos_prev_r = gripper_r_.pos;
  gripper_r_.pos = gripper_r_.calc_servo_angle();
  gripper_r_.vel = (gripper_r_.pos - pos_prev_r) / delta_seconds;

  return hardware_interface::return_type::OK;
}

hardware_interface::return_type ExtenderArduinoHardware::write(
  const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/)
{
  if (!comms_.connected())
  {
    RCLCPP_ERROR(rclcpp::get_logger("ExtenderArduinoHardware"), "Communication not connected.");
    return hardware_interface::return_type::ERROR;
  }

  // Write motor values
  int motor_l_counts_per_loop = wheel_l_.cmd / wheel_l_.rads_per_count / cfg_.loop_rate;
  int motor_r_counts_per_loop = wheel_r_.cmd / wheel_r_.rads_per_count / cfg_.loop_rate;
  RCLCPP_DEBUG(rclcpp::get_logger("ExtenderArduinoHardware"), "Writing motor values: %d", motor_l_counts_per_loop);
  comms_.set_motor_values(motor_l_counts_per_loop, motor_r_counts_per_loop);

  // Write servo values
  int servo_l_degrees = gripper_l_.cmd * 180 / M_PI;
  int servo_r_degrees = gripper_r_.cmd * 180 / M_PI;
  RCLCPP_DEBUG(
    rclcpp::get_logger("ExtenderArduinoHardware"), "Writing servo values: %d %d", servo_l_degrees,
    servo_r_degrees);
  comms_.set_servo_values(servo_l_degrees, servo_r_degrees);

  return hardware_interface::return_type::OK;
}

}  // namespace extender_arduino

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(
  extender_arduino::ExtenderArduinoHardware, hardware_interface::SystemInterface)
