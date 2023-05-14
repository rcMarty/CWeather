//
// Created by rc_marty on 23.3.23.
//

#include "io.h"
#include <fstream>
#include <regex>
#include <iostream>
#include "colors.h"

std::string io::get_api_key_from_file(const std::string &path) {
    std::string ret_key;
    std::string tmp;
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Could not open file: " << path << std::endl;
        throw std::runtime_error("Could not open file: " + path + "\nPlease create config file or provide valid path with api key in it.");
    }

    while (getline(file, tmp)) {
        if (tmp.find("> api_key = ") != std::string::npos) {
            std::regex key_regex("(> api_key = )"); //todo mby regex isn't best idea mby convert to json config file
            ret_key = std::regex_replace(tmp, key_regex, std::string(""));
            file.close();
            return ret_key;
        }
    }
    throw std::runtime_error("No API key found in file: " + path + "\nMake sure file is in format \"> api_key = yourApiKey\"");
}

bool io::load_json(const std::string &path, nlohmann::json &json) {
    std::ifstream file;
    try {
        file.open(path);
    }
    catch (const std::exception &e) {
        file.close();
        return false;
    }

    if (!file.is_open()) {
        file.close();
        return false;
    }

    file >> json;
    file.close();
    return true;
}

bool io::save_json(const std::string &path, nlohmann::json &json) {
    std::ofstream file;
    try {
        file.open(path);
        file << json;
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        file.close();
        return false;
    }

    file.close();
    return true;
}

