//
// Created by rc_marty on 23.3.23.
//

#pragma once

#include "3rdparty/json.hpp"
#include "weather/WeatherMoment.h"
#include "weather/Forecast.h"
#include "settings.h"

#include <string>
#include <unordered_map>


class QueryBuilder {
public:
    std::unique_ptr<Settings> settings; //todo remake setting into class Settings
    std::string base_URI = "https://api.weatherapi.com/v1/";
    std::unordered_map<std::string, std::string> params;
    std::string api_key;
    nlohmann::json response;

    std::string build_URL(const std::string &type);
    QueryBuilder(const QueryBuilder &type);

    QueryBuilder(const std::string &key, const std::string &city);

};

class QueryBuilderDay {
    std::unique_ptr<QueryBuilder> builder;
public:

    ~QueryBuilderDay() = default;
    explicit QueryBuilderDay(const QueryBuilder &builder, int days = 1);

    std::vector<std::shared_ptr<weather::Forecast>> get_current_forecast();
    nlohmann::json get_current_forecast_json();
};


class QueryBuilderNow {
    std::unique_ptr<QueryBuilder> builder;
public:
    explicit QueryBuilderNow(const QueryBuilder &builder);
    ~QueryBuilderNow() = default;

    weather::WeatherMoment get_current_weather();
    nlohmann::json get_current_weather_json();
};