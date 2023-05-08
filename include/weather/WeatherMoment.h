//
// Created by rc_marty on 25.3.23.
//

#pragma once

#include <ctime>
#include <string>
#include <memory>
#include "weather/AirQuality.h"
#include "3rdparty/json.hpp"
#include "Astronomy.h"

namespace weather {
/**
     * @brief WeatherMoment contains all important data from one moment in time
     *
     */
    struct WeatherMoment {

        std::time_t time;
        float temp_c;
        float temp_f;
        float feelslike_c;
        float feelslike_f;
        float wind_kph;
        int wind_degree;
        float pressure_mb;
        float precip_mm;
        int humidity;
        float uv;
        std::string condition_text;
        std::unique_ptr<AirQuality> air_quality;
        std::unique_ptr<Astronomy> astronomy;


        WeatherMoment() = default;
        WeatherMoment(const WeatherMoment &type);
        // overload << operator
        friend std::ostream &operator<<(std::ostream &os, const WeatherMoment &weather_moment);


    };
}