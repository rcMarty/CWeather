//
// Created by rc_marty on 8.5.23.
//

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "3rdparty/json.hpp"
#include "weather/Astronomy.h"
#include "colors.h"

using json = nlohmann::json;

namespace parsersJsonFromApi {
    weather::Astronomy parseAstronomy(const json &json) {
        if (!json.contains("sunrise")) {
            std::cout << json << std::endl;
            throw std::runtime_error("[Astronomy]  nothing like \"sunrise\" found \nIs it right part of json?");
        }
        
        weather::Astronomy astronomy = weather::Astronomy();
        astronomy.sunrise = json["sunrise"].get<std::string>();
        astronomy.sunset = json["sunset"].get<std::string>();
        astronomy.moonrise = json["moonrise"].get<std::string>();
        astronomy.moonset = json["moonset"].get<std::string>();
        astronomy.moon_phase = json["moon_phase"].get<std::string>();
        astronomy.moon_illumination = stoi(json["moon_illumination"].get<std::string>());
        return astronomy;
    }
}
