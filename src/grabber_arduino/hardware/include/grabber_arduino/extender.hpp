#ifndef GRABBER_ARDUINO__EXTENDER_HPP_
#define GRABBER_ARDUINO__EXTENDER_HPP_

#include <string>

class Extender
{
public:
    std::string name = "";
    double cmd = 0;
    double pos = 0;
    double vel = 0;

    Extender() = default;

    Extender(const std::string &extender_name)
    {
        setup(extender_name);
    }

    void setup(const std::string &extender_name)
    {
        name = extender_name;
    }

    double get_position() const
    {
        return pos;
    }
};

#endif // GRABBER_ARDUINO__EXTENDER_HPP_
