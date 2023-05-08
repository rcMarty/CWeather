//
// Created by rc_marty on 25.3.23.
//

#include <iostream>
#include "weather/Forecast.h"

std::ostream &weather::operator<<(std::ostream &os, const weather::Forecast &forecast) {
    os << "{" << std::endl;
    os << "    " << "time: " << std::ctime(&forecast.time) << std::endl;
    os << "    " << "max_temp_c: " << forecast.max_temp_c;
    os << "    " << ", min_temp_c: " << forecast.min_temp_c;
    os << "    " << ", avg_temp_c: " << forecast.avg_temp_c << std::endl;
    os << "    " << "max_wind_kph: " << forecast.max_wind_kph << std::endl;
    os << "    " << "total_precip_mm: " << forecast.total_precip_mm << std::endl;
    os << "    " << "condition_text: " << forecast.condition_text << std::endl << std::endl;
    if (forecast.air_quality) {
        os << "    " << "air_quality: " << *forecast.air_quality << std::endl;
    }

    if (forecast.astronomy) {
        os << "    " << "astronomy: " << *forecast.astronomy << std::endl;
    }

    os << "    " << "samples: " << std::endl;
    for (auto &sample: forecast.samples) {
        os << "        " << *sample << std::endl;
    }
    return os;
}


weather::Forecast::Forecast(const weather::Forecast &type) {
    time = type.time;
    max_temp_c = type.max_temp_c;
    max_temp_f = type.max_temp_f;
    min_temp_c = type.min_temp_c;
    min_temp_f = type.min_temp_f;
    avg_temp_c = type.avg_temp_c;
    avg_temp_f = type.avg_temp_f;
    max_wind_kph = type.max_wind_kph;
    total_precip_mm = type.total_precip_mm;
    condition_text = type.condition_text;
    if (type.air_quality) {
        air_quality = std::make_unique<weather::AirQuality>(weather::AirQuality(*type.air_quality));
    }
    if (type.astronomy) {
        astronomy = std::make_unique<weather::Astronomy>(weather::Astronomy(*type.astronomy));
    }
    for (auto &sample: type.samples) {
        samples.push_back(std::make_shared<weather::WeatherMoment>(weather::WeatherMoment(*sample)));
    }
}

