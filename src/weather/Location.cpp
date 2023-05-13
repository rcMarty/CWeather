//
// Created by rc_marty on 13.5.23.
//

#include "weather/Location.h"

std::ostream &operator<<(std::ostream &os, const weather::Location &location) {
    os << "{" << std::endl;
    os << "    " << "city: " << location.city << std::endl;
    os << "    " << "region: " << location.region << std::endl;
    os << "    " << "country: " << location.country << std::endl;
    os << "}," << std::endl;
    return os;
}
