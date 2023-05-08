//
// Created by rc_marty on 25.3.23.
//

#include "queryBuilder.h"
#include "io.h"


#include <iostream> //todo after debugging remove
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include "parsersJson/ForecastJson.h"
#include "parsersJson/WeatherMomentJson.h"
#include "parsersJson/AirQualityJson.h"
#include "parsersJson/AstronomyJson.h"


QueryBuilderDay::QueryBuilderDay(const std::string &key, const std::string &city, int days) : QueryBuilder(key, city) { // todo parsing into object

    params["days"] = std::to_string(days);
    std::ostringstream os;
    os << cURLpp::options::Url(build_URL("forecast"));
    response = nlohmann::json::parse(os.str());

}

std::vector<std::shared_ptr<weather::Forecast>> QueryBuilderDay::get_current_forecast() {
    if (response.empty() || response["forecast"].empty()) {
        std::cout << "Response is empty or there is not key \"forecast\"" << std::endl;
        return std::vector<std::shared_ptr<weather::Forecast>>{};
    }

    std::vector<std::shared_ptr<weather::Forecast>> days;
    //return weather::Forecast(response["forecast"]);
    for (const auto &item: response["forecast"]["forecastday"]) {
        days.push_back(std::make_shared<weather::Forecast>(parsersJson::parseForecast(item)));
    }
    return days;

}

nlohmann::json QueryBuilderDay::get_current_forecast_json() {
    return response;
}

QueryBuilderNow::QueryBuilderNow(const std::string &key, const std::string &city) : QueryBuilder(key, city) {

    std::ostringstream os;
    os << cURLpp::options::Url(build_URL("current"));
    response = nlohmann::json::parse(os.str());
}

weather::WeatherMoment QueryBuilderNow::get_current_weather() {

    if (response.empty() && response["current"].empty()) {
        std::cout << "Response is empty or there is not key \"current\"" << std::endl;
        return weather::WeatherMoment{};
    }
    return weather::WeatherMoment(parsersJson::parseWeatherMoment(response["current"]));

}

nlohmann::json QueryBuilderNow::get_current_weather_json() {
    return response;
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

std::string QueryBuilder::build_URL(const std::string &type) {
    std::string ret = base_URI + type + ".json?";
    for (auto &i: params) {
        ret += i.first + "=" + i.second + "&";
    }
    return ret;
}
