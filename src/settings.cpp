//
// Created by rc_marty on 26.3.23.
//

#include "settings.h"
#include "3rdparty/json.hpp"

using json = nlohmann::json;

Settings::Settings(std::string api_key) : api_key(std::move(api_key)) {

}
void Settings::load(std::string path) {
    if (!io::load_json(path, this->settings)) {
        std::cout << "Could not load settings file: " << path << std::endl;
    }
    api_key = this->settings["api_key"];
    city = this->settings["city"];
    celsius = this->settings["celsius"] == "true";
    aqi = this->settings["aqi"] == "true";
}
void Settings::save(std::string path) {

    this->settings["api_key"] = api_key;
    this->settings["city"] = city;
    this->settings["celsius"] = celsius ? "true" : "false";
    this->settings["aqi"] = aqi ? "true" : "false";
    this->settings["days"] = days;

    if (!io::save_json(path, this->settings)) {
        std::cout << "Could not save settings file: " << path << std::endl;
        throw std::runtime_error("Could not save settings file: " + path);
    }
}
