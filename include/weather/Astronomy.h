//
// Created by rc_marty on 25.3.23.
//

#pragma once

#include "3rdparty/json.hpp"

#include <ctime>
#include <string>

namespace weather {
/**
     * @brief Astronomy contains all data about sun and moon
     */
    struct Astronomy {
        std::string sunrise;
        std::string sunset;
        std::string moonrise;
        std::string moonset;
        std::string moon_phase;
        int moon_illumination;

        //todo normal constructor with gets basic_json
        Astronomy() = default;
        ~Astronomy() = default;

        friend std::ostream &operator<<(std::ostream &os, const Astronomy &astronomy);

    };
}