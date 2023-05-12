//
// Created by rc_marty on 8.5.23.
//
#pragma once

#include "3rdparty/json.hpp"
#include "weather/AirQuality.h"
#include "weather/Astronomy.h"
#include "weather/WeatherMoment.h"
#include "parsersJsonFromApi/AirQualityJson.h"
#include "parsersJsonFromApi/AstronomyJson.h"
#include <string>

using json = nlohmann::json;

namespace parsersJsonFromApi {
    weather::WeatherMoment parseWeatherMoment(const json &json) {
        if (!json.contains("last_updated_epoch") && !json.contains("time_epoch")) {
            std::cout << json << std::endl;
            throw std::runtime_error("[WeatherMoment]  nothing like \"last_updated_epoch\" || \"time_epoch\" and  found \nCURRENT WEATHER\nIs it right part of json?");
        }

        weather::WeatherMoment weatherMoment = weather::WeatherMoment();

        if (json.contains("last_updated_epoch"))
            weatherMoment.time = json["last_updated_epoch"];
        else
            weatherMoment.time = json["time_epoch"];

        weatherMoment.temp_c = json["temp_c"].get<float>();
        weatherMoment.temp_f = json["temp_f"].get<float>();
        weatherMoment.feelslike_c = json["feelslike_c"].get<float>();
        weatherMoment.feelslike_f = json["feelslike_f"].get<float>();
        weatherMoment.wind_kph = json["wind_kph"].get<float>();
        weatherMoment.wind_degree = json["wind_degree"].get<int>();
        weatherMoment.pressure_mb = json["pressure_mb"].get<float>();
        weatherMoment.precip_mm = json["precip_mm"].get<float>();
        weatherMoment.humidity = json["humidity"].get<int>();
        weatherMoment.uv = json["uv"].get<float>();
        weatherMoment.condition_text = json["condition"]["text"].get<std::string>();


        if (json.contains("air_quality")) {
            weatherMoment.air_quality = std::make_unique<weather::AirQuality>(parsersJsonFromApi::parseAirQuality(json["air_quality"]));
        }
        if (json.contains("astronomy")) {
            weatherMoment.astronomy = std::make_unique<weather::Astronomy>(parsersJsonFromApi::parseAstronomy(json["astronomy"]));
        }
        return weatherMoment;
    }
}
