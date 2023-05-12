//
// Created by rc_marty on 25.3.23.
//

#include "weather/Astronomy.h"
#include <iostream>


std::ostream &weather::operator<<(std::ostream &os, const weather::Astronomy &astronomy) {
    os << "{" << std::endl;
    os << "    " << "sunrise: " << astronomy.sunrise << std::endl;
    os << "    " << "sunset: " << astronomy.sunset << std::endl;
    os << "    " << "moonrise: " << astronomy.moonrise << std::endl;
    os << "    " << "moonset: " << astronomy.moonset << std::endl;
    os << "    " << "moon_phase: " << astronomy.moon_phase << std::endl;
    os << "    " << "moon_illumination: " << astronomy.moon_illumination << std::endl;
    os << "}," << std::endl;
    return os;
}
//void weather::Astronomy::accept(Visitors::Visitor &v) const {
//    v.visit(*this);
//}
