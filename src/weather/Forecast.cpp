//
// Created by rc_marty on 25.3.23.
//

#include <iostream>
#include "weather/Forecast.h"

std::ostream &weather::operator<<(std::ostream &os, const weather::Forecast &forecast) {
    os << "{" << std::endl;
    os << "    " << "time: " << std::ctime(&forecast.time) << std::endl;
    os << "    " << "max_temp_c: " << forecast.max_temp_c;
    os << "    " << ", min_temp_c: " << forecast.min_temp_c;
    os << "    " << ", avg_temp_c: " << forecast.avg_temp_c << std::endl;
    os << "    " << "max_wind_kph: " << forecast.max_wind_kph << std::endl;
    os << "    " << "total_precip_mm: " << forecast.total_precip_mm << std::endl;
    os << "    " << "condition_text: " << forecast.condition_text << std::endl << std::endl;


    if (forecast.astronomy != nullptr) {
        os << "    " << "astronomy: " << *forecast.astronomy << std::endl;
    }

    os << "    " << "samples: " << std::endl;
    for (auto &sample: forecast.samples) {
        os << "          " << *sample << std::endl;
    }
    return os;
}


weather::Forecast::Forecast(const weather::Forecast &type) {
    time = type.time;
    max_temp_c = type.max_temp_c;
    max_temp_f = type.max_temp_f;
    min_temp_c = type.min_temp_c;
    min_temp_f = type.min_temp_f;
    avg_temp_c = type.avg_temp_c;
    avg_temp_f = type.avg_temp_f;
    max_wind_kph = type.max_wind_kph;
    total_precip_mm = type.total_precip_mm;
    condition_text = type.condition_text;


    astronomy = std::make_unique<weather::Astronomy>(weather::Astronomy(*type.astronomy));

    for (auto &sample: type.samples) {
        samples.push_back(std::make_shared<weather::WeatherMoment>(weather::WeatherMoment(*sample)));
    }
}
std::string weather::Forecast::get_simple_output(const Settings &settings) const {
    std::string output;

    time_t rawtime = this->time;
    auto tim = std::time(&rawtime);
    output += std::string("\tDate: ") + std::ctime(&tim) + "\n";
    
    if (settings.celsius) {
        output += "Max temp: " + std::to_string(max_temp_c) + "°C" + "\t\t";
        output += "Min temp: " + std::to_string(min_temp_c) + "°C" + "\n";
    } else {
        output += "Max temp: " + std::to_string(max_temp_f) + "°F" + "\t\t";
        output += "Min temp: " + std::to_string(min_temp_f) + "°F" + "\n";
    }

    output += "Max wind speed: " + std::to_string(max_wind_kph) + "km/h" + "\n";
    output += "Total precipitation: " + std::to_string(total_precip_mm) + "mm" + "\n";
    output += "Condition: " + condition_text + "\n";

    if (settings.astronomy) {
        output += "Sunrise: " + astronomy->sunrise + "\n";
        output += "Sunset: " + astronomy->sunset + "\n";
        output += "Moon Illumination:" + std::to_string(astronomy->moon_illumination) + "\n";
    }

    return output;


}




//void weather::Forecast::accept(Visitors::Visitor &v) const {
//    v.visit(*this);
//}
