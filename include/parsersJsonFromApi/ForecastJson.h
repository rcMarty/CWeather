//
// Created by rc_marty on 8.5.23.
//

#pragma once

#include "3rdparty/json.hpp"
#include "weather/Forecast.h"
#include "parsersJsonFromApi/AstronomyJson.h"
#include "parsersJsonFromApi/AirQualityJson.h"
#include "parsersJsonFromApi/WeatherMomentJson.h"
#include <string>
#include "colors.h"


using json = nlohmann::json;

namespace parsersJsonFromApi {
    weather::Forecast parseForecast(const json &json) {
        if (!json.contains("day")) {
            std::cout << json << std::endl;
            throw std::runtime_error("[Forecast]  nothing like \"day\" found \nIs it right part of json?");
        }
        weather::Forecast forecast = weather::Forecast();
        forecast.time = json["date_epoch"];
        forecast.max_temp_c = json["day"]["maxtemp_c"].get<float>();
        forecast.max_temp_f = json["day"]["maxtemp_f"].get<float>();
        forecast.min_temp_c = json["day"]["mintemp_c"].get<float>();
        forecast.min_temp_f = json["day"]["mintemp_f"].get<float>();
        forecast.avg_temp_c = json["day"]["avgtemp_c"].get<float>();
        forecast.avg_temp_f = json["day"]["avgtemp_f"].get<float>();
        forecast.max_wind_kph = json["day"]["maxwind_kph"].get<float>();
        forecast.total_precip_mm = json["day"]["totalprecip_mm"].get<float>();
        forecast.condition_text = json["day"]["condition"]["text"];


        if (json.contains("astro")) {
            forecast.astronomy = std::make_unique<weather::Astronomy>(parsersJsonFromApi::parseAstronomy(json["astro"]));
        }
        
        for (auto &hour: json["hour"]) {
            forecast.samples.push_back(std::make_shared<weather::WeatherMoment>(parsersJsonFromApi::parseWeatherMoment(hour)));
        }
        return forecast;
    }
}

