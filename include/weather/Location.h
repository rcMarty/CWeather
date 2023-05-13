//
// Created by rc_marty on 13.5.23.
//
#pragma once

#include "3rdparty/json.hpp"
#include <string>

namespace weather {
    /**
     * @brief Location contains all basic data about location
     */
    struct Location {
        std::string city;
        std::string region;
        std::string country;

        Location() = default;
        Location(const Location &type) = default;
        friend std::ostream &operator<<(std::ostream &os, const Location &location);
    };
}

