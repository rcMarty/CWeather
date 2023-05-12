//
// Created by rc_marty on 25.3.23.
//

#include <iostream>
#include "weather/WeatherMoment.h"

std::ostream &weather::operator<<(std::ostream &os, const weather::WeatherMoment &weather_moment) {
    os << "{" << std::endl;
    os << "    " << "time: " << std::ctime(&weather_moment.time) << std::endl;
    os << "    " << "temp_c: " << weather_moment.temp_c;
    os << "    " << ", feelslike_c: " << weather_moment.feelslike_c << std::endl;
    os << "    " << "wind_kph: " << weather_moment.wind_kph;
    os << "    " << ", wind_degree: " << weather_moment.wind_degree << std::endl;
    os << "    " << "pressure_mb: " << weather_moment.pressure_mb << std::endl;
    os << "    " << "precip_mm: " << weather_moment.precip_mm << std::endl;
    os << "    " << "humidity: " << weather_moment.humidity << std::endl;
    os << "    " << "uv: " << weather_moment.uv << std::endl;
    os << "    " << "condition_text: " << weather_moment.condition_text << std::endl;
    if (weather_moment.air_quality) {
        os << "    " << "air_quality: " << *weather_moment.air_quality << std::endl;
    }
    if (weather_moment.astronomy) {
        os << "    " << "astronomy: " << *weather_moment.astronomy << std::endl;
    }

    os << "}," << std::endl;
    return os;
}


weather::WeatherMoment::WeatherMoment(const weather::WeatherMoment &type) {
    time = type.time;
    temp_c = type.temp_c;
    temp_f = type.temp_f;
    feelslike_c = type.feelslike_c;
    feelslike_f = type.feelslike_f;
    wind_kph = type.wind_kph;
    wind_degree = type.wind_degree;
    pressure_mb = type.pressure_mb;
    precip_mm = type.precip_mm;
    humidity = type.humidity;
    uv = type.uv;
    condition_text = type.condition_text;
    if (type.air_quality) {
        air_quality = std::make_unique<weather::AirQuality>(*type.air_quality);
    }
    if (type.astronomy) {
        astronomy = std::make_unique<weather::Astronomy>(*type.astronomy);
    }
}
//void weather::WeatherMoment::accept(Visitors::Visitor &v) const {
//     v.visit(*this);
//}
