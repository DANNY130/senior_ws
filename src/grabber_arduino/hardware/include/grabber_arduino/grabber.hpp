#ifndef GRABBER_ARDUINO__GRABBER_HPP_
#define GRABBER_ARDUINO__GRABBER_HPP_

#include <string>

class Grabber
{
public:
  Grabber(const std::string & name, int servo_pin);

  void update_state(double position);
  void set_command(double command);

  double get_position() const;
  double get_command() const;

private:
  std::string name_;
  int servo_pin_;
  double position_;
  double command_;
};

#endif  // GRABBER_ARDUINO__GRABBER_HPP_
