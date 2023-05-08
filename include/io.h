//
// Created by rc_marty on 23.3.23.
//

#pragma once

#include "3rdparty/json.hpp"
#include <string>

namespace io {
    std::string get_api_key_from_file(const std::string &path);

    bool load_json(const std::string &path, nlohmann::json &json);
    bool save_json(const std::string &path, nlohmann::json &json);


}



