//
// Created by rc_marty on 8.5.23.
//

#pragma once

#include <string>
#include <iostream>
#include "3rdparty/json.hpp"
#include "weather/AirQuality.h"

using json = nlohmann::json;

namespace parsersJsonFromApi {
    weather::AirQuality parseAirQuality(const json &json) {
        if (!json.contains("co")) {
            std::cout << json << std::endl;
            throw std::runtime_error("[AirQuality]  nothing like \"co\"found \nIs it right part of json?");
        }
        weather::AirQuality airQuality = weather::AirQuality();
        airQuality.co = json["co"].get<double>();
        airQuality.no2 = json["no2"].get<double>();
        airQuality.o3 = json["o3"].get<double>();
        airQuality.so2 = json["so2"].get<double>();
        return airQuality;
    }
}



