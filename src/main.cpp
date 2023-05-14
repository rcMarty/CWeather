//
// Created by rc_marty on 23.3.23.
//

#include "3rdparty/json.hpp"
#include "io.h"
#include "queryBuilder.h"
#include "UI/consoleUI.h"
#include <CLI11.hpp>

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

int main(int argc, char **argv) {

    CLI::App app{"Weather app"};
    app.set_help_all_flag("--help-all", "Expand all help");

    CLI::App *current = app.add_subcommand("current", "Current weather");
    CLI::App *forecast = app.add_subcommand("forecast", "Forecast weather");
    CLI::App *settings = app.add_subcommand("settings", "Settings");
    app.require_subcommand(1);
    string city;
    string key;
    bool simple = false;
    bool aqi = false;
    int days{0};
    bool temp{false};
    bool rain{false};
    char units{};
    bool astronomy{false};
    bool feels{false};
    string savefilepath;
    string loadfilepath;
    auto settin = std::make_unique<Settings>("");
    settin->load("settinngs.json");

    current->add_option("-c,--city", city, "City name");
    current->add_flag("-s,--simple", simple, "Simple output");
    current->add_option("-k,--file-key", key, "path to config.cfg file with api key | also you can make Settings");


    current->callback([&]() {


        if (settin->api_key == "") {
            cout << "path to key: " << key << endl;
            cout << "city: " << (city == "" ? "searching by auto ip" : city) << endl;
            settin->api_key = io::get_api_key_from_file(key);
        }
        settin->city = (city == "" ? settin->city : city);

        auto query = std::make_unique<QueryBuilderNow>(QueryBuilder(*settin));
        auto loc = query->builder->get_location();
        auto weather = query->get_current_weather();
        std::cout << "Searching for city: " << loc.city << ", " << loc.country << std::endl;
        if (simple) {
            std::cout << weather.get_simple_output(*settin) << std::endl;
        } else
            std::cout << weather << std::endl;


    });


    forecast->add_option("-k,--file-key", key, "path to config.cfg file with api key | also you can make Settings");
    forecast->add_option("-c,--city", city, "City name");
    forecast->add_option("-d,--days", days, "Number of days to forecast");
    forecast->add_option("--save", savefilepath, "Save Forecast to file");
    forecast->add_option("--load", loadfilepath, "Load Forecast from file");

    forecast->add_flag("-t,--temp", temp, "Show temperature graph");
    forecast->add_flag("-r,--rain", rain, "Show rain graph");
    forecast->add_flag("-s,--simple", simple, "Simple output");
    forecast->add_flag("-a,--astronomy", astronomy, "Show astronomy data");
    forecast->add_flag("-q,--aqi", aqi, "Show Quality of Air");
    forecast->add_flag("-f,--feels", feels, "Show feels like temperature");


    forecast->callback([&]() {
        if (settin->api_key == "") {
            settin->api_key = io::get_api_key_from_file(key);
            cout << "path to key: " << key << endl;
            cout << "city: " << (city == "" ? "searching by auto ip" : city) << endl;
            cout << "days: " << (days == 0 ? "displaying one day" : std::to_string(days)) << endl;
        }

        settin->city = (city == "" ? settin->city : city);
        settin->days = (days == 0 ? settin->days : days);
        settin->aqi = aqi;
        settin->astronomy = astronomy;
        settin->feels = feels;


        auto query = std::make_unique<QueryBuilderDay>(QueryBuilder(*settin));

        if (!savefilepath.empty()) {
            if (io::save_json(savefilepath, query->builder->response))
                cout << "Saved to: " << savefilepath << endl;
            else
                cout << "Error while saving to: " << savefilepath << endl;
        }
        if (!loadfilepath.empty()) {
            if (io::load_json(loadfilepath, query->builder->response))
                cout << "Loaded from: " << loadfilepath << endl;
            else
                cout << "Error while loading from: " << loadfilepath << endl;
        }

        //cout << query->builder->response << endl;
        auto loc = query->builder->get_location();
        auto weather = query->get_current_forecast();


        std::cout << "Searching for city: " << loc.city << ", " << loc.country << std::endl;
        if (rain) {
            std::cout << graph::get_precip_graph(weather, "Rain", *settin) << std::endl;
        } else if (temp) {
            std::cout << graph::get_temperature_graph(weather, "Temperature", *settin) << std::endl;
        } else if (simple) {
            for (const auto &i: weather) {
                std::cout << i->get_simple_output(*settin) << std::endl;
            }
        } else {
            for (const auto &i: weather) {
                std::cout << *i << std::endl;
            }
        }
    });


    settings->add_option("-k,--file-key", key, "path to config.cfg file with api key | also you can make Settings")->required();
    settings->add_option("-c,--city", city, "City name");
    settings->add_option("-d,--days", days, "Number of days to forecast");
    settings->add_option("-u,--units", units, "Units of temperature (c/f) c->celsius, f->fahrenheit");
    settings->add_flag("-a,--astronomy", astronomy, "Show astronomy data");
    settings->add_flag("-q,--aqi", aqi, "Show Quality of Air");
    settings->add_flag("-f,--feels", feels, "Show feels like temperature");
    settings->callback([&]() {
        cout << "path to key: " << key << endl;
        settin->api_key = io::get_api_key_from_file(key);
        settin->city = (city.empty() ? settin->city : city);
        settin->days = (days == 0 ? settin->days : days);
        settin->aqi = aqi;
        if (units == 'f')
            settin->celsius = false;
        else if (units == 'c')
            settin->celsius = true;
        else
            cout << "No recognizable units, using normal C" << endl;
        settin->astronomy = units;
        settin->feels = feels;
        settin->aqi = aqi;
        settin->save("settinngs.json");
    });


    CLI11_PARSE(app, argc, argv);


}
