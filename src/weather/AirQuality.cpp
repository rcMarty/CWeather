//
// Created by rc_marty on 25.3.23.
//

#include <iostream>
#include "weather/AirQuality.h"

std::ostream &weather::operator<<(std::ostream &os, const weather::AirQuality &air_quality) {
    os << "{" << std::endl;
    os << "    " << "co: " << air_quality.co << std::endl;
    os << "    " << "no2: " << air_quality.no2 << std::endl;
    os << "    " << "o3: " << air_quality.o3 << std::endl;
    os << "    " << "so2: " << air_quality.so2 << std::endl;
    os << "    " << "}," << std::endl;
    return os;
}




