//
// Created by rc_marty on 25.3.23.
//

#include "queryBuilder.h"
#include "io.h"


#include <iostream> //todo after debugging remove
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include "parsersJsonFromApi/ForecastJson.h"
#include "parsersJsonFromApi/WeatherMomentJson.h"
#include "parsersJsonFromApi/AirQualityJson.h"
#include "parsersJsonFromApi/AstronomyJson.h"


std::string QueryBuilder::build_URL(const std::string &type) {
    std::string ret = base_URI + type + ".json?";
    for (auto &i: params) {
        ret += i.first + "=" + i.second + "&";
    }
    return ret;
}
QueryBuilder::QueryBuilder(const QueryBuilder &type) {
    this->api_key = type.api_key;
    this->base_URI = type.base_URI;
    this->params = type.params;
    this->response = type.response;
}


QueryBuilderDay::QueryBuilderDay(const QueryBuilder &builder, int days) { // todo parsing into object
    this->builder = std::make_unique<QueryBuilder>(builder);
    this->builder->params["days"] = std::to_string(days);

    std::ostringstream os;
    os << cURLpp::options::Url(this->builder->build_URL("forecast"));
    this->builder->response = nlohmann::json::parse(os.str());

}

std::vector<std::shared_ptr<weather::Forecast>> QueryBuilderDay::get_current_forecast() {
    if (this->builder->response.empty() || this->builder->response["forecast"].empty()) {
        std::cout << "Response is empty or there is not key \"forecast\"" << std::endl;
        return std::vector<std::shared_ptr<weather::Forecast>>{};
    }

    std::vector<std::shared_ptr<weather::Forecast>> days;
    //return weather::Forecast(response["forecast"]);
    for (const auto &item: this->builder->response["forecast"]["forecastday"]) {
        days.push_back(std::make_shared<weather::Forecast>(parsersJsonFromApi::parseForecast(item)));
    }

    return days;

}

nlohmann::json QueryBuilderDay::get_current_forecast_json() {
    return this->builder->response;
}

QueryBuilderNow::QueryBuilderNow(const QueryBuilder &builder) {
    this->builder = std::make_unique<QueryBuilder>(builder);
    std::ostringstream os;
    os << cURLpp::options::Url(this->builder->build_URL("current"));
    this->builder->response = nlohmann::json::parse(os.str());
}

weather::WeatherMoment QueryBuilderNow::get_current_weather() {

    if (this->builder->response.empty() && this->builder->response["current"].empty()) {
        std::cout << "Response is empty or there is not key \"current\"" << std::endl;
        return weather::WeatherMoment{};
    }
    return weather::WeatherMoment(parsersJsonFromApi::parseWeatherMoment(this->builder->response["current"]));

}

nlohmann::json QueryBuilderNow::get_current_weather_json() {
    return this->builder->response;
}


QueryBuilder::QueryBuilder(const std::string &key, const std::string &city = "auto:ip") {

    if (settings == nullptr) {
        std::cout << "No settings found" << std::endl;
    }

    //todo response error handling

    api_key = key;
    params["key"] = api_key;
    params["q"] = city;
    //params["aqi"] = (json_exists ? std::string(settings["aqi"]) : "no"); //that main
    params["aqi"] = "no";


    //todo check if there isn't key already
    //todo optional params
//    if (!settings["optional"].empty()) {
//        for (auto &i: settings["optional"]) {
//            for (auto &j: i.items()) {
//                params[j.key()] = j.value().get<std::string>();
//            }
//        }
//    }


}


