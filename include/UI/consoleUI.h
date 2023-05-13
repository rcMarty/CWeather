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

namespace usecases {
    std::string get_weather(const std::shared_ptr<weather::WeatherMoment> &weatherMoment);
    std::string get_forecast(const std::vector<std::shared_ptr<weather::Forecast>> &forecast);
    std::string save_forecst(const std::vector<std::shared_ptr<weather::Forecast>> &forecast, const std::string &filename);
    weather::Forecast get_forecast_from_file(const std::string &filename);
    weather::Forecast get_forecast(const std::string &city);

    std::string graph_temperature(const std::vector<std::shared_ptr<weather::Forecast>> &forecast, const std::string &title, Settings &settings);
    std::string graph_temperature_feels(const std::vector<std::shared_ptr<weather::Forecast>> &forecast, const std::string &title, Settings &settings);
    std::string graph_precip(const std::vector<std::shared_ptr<weather::Forecast>> &forecast, const std::string &title, Settings &settings);
    void create_settings();


}

