//
// Created by rc_marty on 23.3.23.
//

#include "3rdparty/json.hpp"
#include "io.h"
#include "queryBuilder.h"

#include <memory>
#include <string>
#include <iostream>


using std::string;
using std::cout;
using std::endl;
using json = nlohmann::json;

int main() {
//
//    curlpp::Cleanup myCleanup;
//
//    // Send request and get a result.
//    // Here I use a shortcut to get it in a string stream ...
//
//    std::ostringstream os;
//    os << curlpp::options::Url(std::string("https://api.weatherapi.com/v1/ip.json?key=5528a1a55b054dd1913172922232303&q=auto:ip&aqi=yes"));
//    string jsonString = os.str();
//
//    // Parse JSON
//    json j = json::parse(jsonString);
//
//    cout << std::setw(4) << j << endl;
//
//    auto f = std::make_unique<weather::Forecast>(weather::Forecast());
//    f->time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
//    for (size_t i = 0; i < 10; i++) {
//        f->samples.push_back(std::make_unique<weather::WeatherMoment>(weather::WeatherMoment{
//                .time = std::time(0),
//                .temp_c = 10.0,
//                .temp_f = 50.0,
//                .feelslike_c = 10.0,
//                .feelslike_f = 50.0,
//                .wind_kph = 10.0,
//                .wind_degree = 10,
//                .pressure_mb = 10.0,
//                .precip_mm = 10.0,
//                .humidity = 10,
//                .uv = 10.0,
//                .condition_text = "test",
//                .air_quality = std::make_unique<weather::AirQuality>(weather::AirQuality{
//                        .co = 10.0,
//                        .no2 = 10.0,
//                        .o3 = 10.0,
//                        .so2 = 10.0
//                })}));
//    }
//    std::cout << f << std::endl;
//
//
//    std::string ret_key;
//    std::string tmp = "#KEY: 123";
//
//    if (tmp.find("#KEY:") != std::string::npos) {
//        std::regex key_regex("[#KEYkey:\\s+]");
//        ret_key = std::regex_replace(tmp, key_regex, std::string(""));
//
//    }
//    std::cout << "." << ret_key << "." << std::endl;
//
//
//    std::vector<std::string> params;
//
//    nlohmann::json inputjson;
//    nlohmann::json scndjson;
//    scndjson["testy0"] = "test";
//    scndjson["testy1"] = "test2";
//    inputjson["alerts"] += scndjson;
//
//
//    inputjson["key"] = "123";
//    inputjson["city"] = "Bratislava";
//    inputjson["days"] = 3;
//    inputjson["aqi"] = "yes";
//    inputjson["alerts"][0]["alert"] = "1st alert";
//    inputjson["alerts"][1]["alert"] = "2nd alert";
//
//
//    for (int i = 0; i < 10; i++) {
//        inputjson["optional"][0][("test" + std::to_string(i * 8))] = "test" + std::to_string(i);
//    }
//
//    std::ofstream fileo("setings.json");
//
//    fileo << inputjson;
//    fileo.close();
//
//
//    nlohmann::json json;
//    std::string path = "setings.json";
//    std::ifstream file(path);
//    if (!file.is_open()) {
//        throw std::runtime_error("Could not open file: " + path);
//    }
//    file >> json;
//    file.close();
//
//
//    if (!json["optional"].empty()) {
//        for (auto &i: json["optional"]) {
//            std::cout << i << std::endl;
//            for (auto &j: i.items()) {
//                params.push_back(j.key() + "=" + j.value().get<std::string>());
//
//            }
//        }
//    }
//
//
//    cout << json["alerts"].contains("a") << endl;
//    cout << std::setw(4) << json << endl;
//
//    params.emplace_back("TAK TROCHU JINÝ TEST");
//    for (auto i: params) {
//        std::cout << i << std::endl;
//    }

    //auto aaa = std::make_unique<QueryBuilderNow>(io::get_api_key_from_file("settings.txt"), "Ostrava");
    //auto a = aaa->get_current_weather();

    auto bbb = std::make_unique<QueryBuilderDay>(QueryBuilder(io::get_api_key_from_file("settings.txt"), "Ostrava"), 3);
    auto b = bbb->get_current_forecast();

    auto bb = *b[0];

    std::cout << bbb->get_current_forecast_json() << std::endl;

    std::cout << *b[0] << std::endl;
    std::cout << *b[1] << std::endl;
    std::cout << *b[2] << std::endl;

}
