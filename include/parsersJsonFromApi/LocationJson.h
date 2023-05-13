//
// Created by rc_marty on 13.5.23.
//


#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "3rdparty/json.hpp"
#include "weather/Location.h"
#include <optional>


using json = nlohmann::json;

namespace parsersJsonFromApi {
    weather::Location parseLocation(const json &json) {
        if (!json.contains("region")) {
            std::cout << json << std::endl;
            throw std::runtime_error("[Location]  nothing like \"region\" found \nIs it right part of json?");
        }
        weather::Location location = weather::Location();
        location.city = json["name"].get<std::string>();
        location.region = json["region"].get<std::string>();
        location.country = json["country"].get<std::string>();

        return location;
    }
}
