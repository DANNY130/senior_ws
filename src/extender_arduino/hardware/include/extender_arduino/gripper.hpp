#ifndef EXTENDER_ARDUINO_GRIPPER_HPP
#define EXTENDER_ARDUINO_GRIPPER_HPP

#include <string>
#include <cmath>

class Gripper
{
public:
  std::string name = "";
  double cmd = 0;
  double pos = 0;
  double vel = 0;
  double degrees = 0;  // Change from int to double

  Gripper() = default;

  Gripper(const std::string &gripper_name)
  {
    setup(gripper_name);
  }

  void setup(const std::string &gripper_name)
  {
    name = gripper_name;
  }

  double calc_servo_angle()
  {
    double radians = degrees * M_PI / 180.0;
    return radians;
  }
};

#endif // EXTENDER_ARDUINO_GRIPPER_HPP
