//
// Created by rc_marty on 23.3.23.
//

#include "io.h"
#include <fstream>
#include <regex>

std::string io::get_api_key_from_file(const std::string &path) {
    std::string ret_key;
    std::string tmp;
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + path);
    }

    while (getline(file, tmp)) {
        if (tmp.find("#KEY:") != std::string::npos) {
            std::regex key_regex("[#KEYkey:\\s+]"); //todo mby regex isn't best idea mby convert to json config file
            ret_key = std::regex_replace(tmp, key_regex, std::string(""));
            file.close();
            return ret_key;
        }
    }
    throw std::runtime_error("No API key found in file: " + path);
}

bool io::load_json(const std::string &path, nlohmann::json &json) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }
    file >> json;
    file.close();
    return true;
}

bool io::save_json(const std::string &path, nlohmann::json &json) {
    std::ofstream file(path);
    file << json;
    file.close();
    return true;
}

