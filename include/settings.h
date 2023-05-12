
//
// Created by rc_marty on 26.3.23.
//
#pragma once

#include "3rdparty/json.hpp"
#include "io.h"
#include <string>
#include <iostream>

class Settings {
private:
    nlohmann::json settings;
    std::string settings_path = "settings.json";
public:
    bool celsius = true;
    std::string api_key;
    std::string city = "Ostrava";
    bool aqi = true;
    int days = 1;
    Settings(std::string api_key);
    ~Settings() = default;

    void load(std::string path);
    void save(std::string path);
};
