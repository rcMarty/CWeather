//
// Created by rc_marty on 23.3.23.
//

#include "3rdparty/json.hpp"
#include "io.h"
#include "queryBuilder.h"
#include "UI/consoleUI.h"

#include <memory>
#include <string>
#include <iostream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>


using std::string;
using std::cout;
using std::endl;
using json = nlohmann::json;

int main() {

    //curlpp::Cleanup myCleanup;

    // Send request and get a result.
    // Here I use a shortcut to get it in a string stream ...

//    std::ostringstream os;
//    os << curlpp::options::Url(std::string("https://api.weatherapi.com/v1/ip.json?key=5528a1a55b054dd1913172922232303&q=auto:ip&aqi=yes"));
//    string jsonString = os.str();
//
//    // Parse JSON
//    json j = json::parse(jsonString);
//
//    cout << std::setw(4) << j << endl;

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


//    std::string ret_key;
//    std::string tmp = "#KEY: 123";
//
//    if (tmp.find("#KEY:") != std::string::npos) {
//        std::regex key_regex("[#KEYkey:\\s+]");
//        ret_key = std::regex_replace(tmp, key_regex, std::string(""));
//    }
//
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

    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;


    auto settin = std::make_unique<Settings>(io::get_api_key_from_file("settings.txt"));
    settin->city = "Ostrava";
    settin->celsius = true;
    settin->days = 10;
    settin->save("settings.json");

//    auto aaa = std::make_unique<QueryBuilderNow>(QueryBuilder(*settin));
//    auto a = aaa->get_current_weather();
//    auto js = aaa->get_current_weather_json();
//    io::save_json("weather.json", js);

    auto bbb = std::make_unique<QueryBuilderDay>(QueryBuilder(*settin), 7);
    auto b = bbb->get_current_forecast();
    auto js2 = bbb->get_current_forecast_json();
    io::save_json("forecast.json", js2);

    //auto bb = *b[0];


    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;

    //cout << b << endl;
    //cout << graph::get_temperature_graph(b, "Teplota", *settin) << endl;
    cout << graph::get_precip_graph(b, "Srážky", *settin) << endl;

    //std::cout << bbb->get_current_forecast_json() << std::endl;

    //std::cout << *b[0] << std::endl;
    //std::cout << *b[1] << std::endl;
    //std::cout << *b[2] << std::endl;

    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;


//    auto graph = std::vector<int>{3, 4, 5, 6, 5, 4, 3, 4, 5, 6, 0, 0, 9, 10, 11, 10, 10, 9, 9, 7, 6, 5, 6};
//    cout << graph::generate_graph(graph, "Moc pěkný graf") << endl;




}
