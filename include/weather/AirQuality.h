//
// Created by rc_marty on 25.3.23.
//
#pragma once

#include "3rdparty/json.hpp"
#include <ostream>

namespace weather {
/**
 * @brief AirQuality contains all basic data about air quality
 */
    struct AirQuality {
        double co;
        double no2;
        double o3;
        double so2;


        AirQuality() = default;

        friend std::ostream &operator<<(std::ostream &os, const AirQuality &air_quality);


    };
}