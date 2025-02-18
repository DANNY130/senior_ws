#ifndef EXAMPLE3_EXTENDER_HPP
#define EXAMPLE3_EXTENDER_HPP

#include "motor.hpp"

namespace example3 {

class Extender {
public:
    std::string name = "";
    int enc = 0;
    double cmd = 0;
    double pos = 0;
    double vel = 0;
    double rads_per_count = 0;

    Extender() = default;

    Extender(const std::string &extender_name, int counts_per_rev) {
        setup(extender_name, counts_per_rev);
    }

    void setup(const std::string &extender_name, int counts_per_rev) {
        name = extender_name;
        rads_per_count = (2 * M_PI) / counts_per_rev;
    }

    double position() {
        double revolutions = enc * rads_per_count / (2 * M_PI);
        double position_meters = revolutions * 0.120;
        return position_meters;
    }
};

} // namespace example3

#endif // EXAMPLE3_EXTENDER_HPP