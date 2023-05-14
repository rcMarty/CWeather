//
// Created by rc_marty on 12.5.23.
//

#pragma once

#include <string>
#include <vector>
#include "weather/Forecast.h"
#include "settings.h"

namespace graph {
    std::string generate_graph(const std::vector<int> &data, const std::string &title);
    std::string get_temperature_graph(const std::vector<std::shared_ptr<weather::Forecast>> &forecast, const std::string &title, Settings &settings);
    std::string get_temperature_feels_graph(const std::vector<std::shared_ptr<weather::Forecast>> &forecast, const std::string &title, Settings &settings);
    std::string get_precip_graph(const std::vector<std::shared_ptr<weather::Forecast>> &forecast, const std::string &title, Settings &settings);
}
