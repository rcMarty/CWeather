//
// Created by rc_marty on 25.3.23.
//

#pragma once


#include <ctime>
#include <string>
#include <memory>
#include <vector>
#include "weather/AirQuality.h"
#include "weather/WeatherMoment.h"
#include "Astronomy.h"

namespace weather {

/**
 * @brief Forecast contains all data about weather forecast per one hour
 * @param samples vector of WeatherMoment
 */
    struct Forecast {

        std::time_t time;
        float max_temp_c;
        float max_temp_f;
        float min_temp_c;
        float min_temp_f;
        float avg_temp_c;
        float avg_temp_f;
        float max_wind_kph;
        float total_precip_mm;
        std::string condition_text;
        std::unique_ptr<AirQuality> air_quality;
        std::unique_ptr<Astronomy> astronomy;
        std::vector<std::shared_ptr<WeatherMoment>> samples; //jak moc tady musí být unique pinter? // todo unique_ptr ???

        Forecast() = default;
        Forecast(Forecast const &type);

        friend std::ostream &operator<<(std::ostream &os, const Forecast &forecast);
    };
}