//
// Created by rc_marty on 12.5.23.
//

#include "UI/consoleUI.h"
#include <iostream>
#include "colors.h"


//
std::string graph::generate_graph(const std::vector<int> &data, const std::string &title) {
    auto origmax = std::max_element(data.begin(), data.end());
    auto origmin = std::min_element(data.begin(), data.end());
    //std::cout << *origmax << " " << *origmin << std::endl;

    std::vector<int> transformed = std::vector<int>(data.size());
    auto range = 0;
    if (*origmin <= 0) {
        std::transform(data.begin(), data.end(), transformed.begin(), [origmin](int i) { return i - *origmin + 1; });
        range = *origmax - *origmin + 1;
    } else {
        transformed = data;
        range = *origmax + 1;
    }


    auto max = std::max_element(transformed.begin(), transformed.end());
    auto min = std::min_element(transformed.begin(), transformed.end());
    //std::cout << *max << " " << *min << std::endl;

    std::vector<std::string> lines(range + 1);
    int zeroLineIndex = *origmax + 1;

    for (int i = lines.size(); i > 0; i--) {
        lines[i] += std::to_string(zeroLineIndex - i) + "\t";
    }

    for (size_t i = lines.size(); i > 0; i--) {
        for (size_t j = 0; j < transformed.size(); j++) {

            if (transformed[j] == *max - i + 1) {
                lines[i] += "::";
            } else if (zeroLineIndex == i) {
                lines[i] += "--";
            } else {
                lines[i] += "  ";
            }
        }
    }

    std::string ret = title + "\n";
    for (auto &line: lines) {
        ret += line + "\n";
    }

    //std::cout << "graph: " << ret << std::endl;
    return ret;
}
std::string graph::get_temperature_graph(const std::vector<std::shared_ptr<weather::Forecast>> &forecast, const std::string &title, Settings &settings) {

    size_t days = settings.days;
    if (settings.days > forecast.size()) {
        std::cout << YELLOW << "Warning: " << RESET << "days to display is greater than days in forecast" << std::endl;
        std::cout << "Displaying all available days" << std::endl;
        days = forecast.size();
    }
    std::string graphs;
    graphs += RED + std::string(60, '-') + RESET + "\n";
    for (size_t i = 0; i < days; i++) {
        graphs += "Day " + std::to_string(i + 1) + "\n";
        std::vector<int> data;
        if (settings.celsius) {
            for (auto &sample: forecast[i]->samples) {
                data.push_back(sample->temp_c);
            }
        } else {
            for (auto &sample: forecast[i]->samples) {
                data.push_back(sample->temp_f);
            }
        }

        graphs += generate_graph(data, title);
        graphs += "\n";

        if (settings.celsius) {
            graphs += "max: " + std::to_string(forecast[i]->max_temp_c) + " C\n";
            graphs += "min: " + std::to_string(forecast[i]->min_temp_c) + " C\n";
            graphs += "avg: " + std::to_string(forecast[i]->avg_temp_c) + " C\n";
        } else {
            graphs += "max: " + std::to_string(forecast[i]->max_temp_f) + " F\n";
            graphs += "min: " + std::to_string(forecast[i]->min_temp_f) + " F\n";
            graphs += "avg: " + std::to_string(forecast[i]->avg_temp_f) + " F\n";
        }

        graphs += "\n";
        graphs += RED + std::string(60, '-') + RESET + "\n";

    }
    return graphs;
}

std::string graph::get_temperature_feels_graph(const std::vector<std::shared_ptr<weather::Forecast>> &forecast, const std::string &title, Settings &settings) {

    size_t days = settings.days;
    if (settings.days > forecast.size()) {
        std::cout << YELLOW << "Warning: " << RESET << "days to display is greater than days in forecast" << std::endl;
        std::cout << "Displaying all available days" << std::endl;
        days = forecast.size();
    }
    std::string graphs;
    graphs += RED + std::string(60, '-') + RESET + "\n";
    for (size_t i = 0; i < days; i++) {
        graphs += "Day " + std::to_string(i + 1) + "\n";
        std::vector<int> data;
        if (settings.celsius) {
            for (auto &sample: forecast[i]->samples) {
                data.push_back(sample->feelslike_c);
            }
        } else {
            for (auto &sample: forecast[i]->samples) {
                data.push_back(sample->feelslike_f);
            }
        }

        graphs += generate_graph(data, title);
        graphs += "\n";

        if (settings.celsius) {
            graphs += "max: " + std::to_string(forecast[i]->max_temp_c) + " C\n";
            graphs += "min: " + std::to_string(forecast[i]->min_temp_c) + " C\n";
            graphs += "avg: " + std::to_string(forecast[i]->avg_temp_c) + " C\n";
        } else {
            graphs += "max: " + std::to_string(forecast[i]->max_temp_f) + " F\n";
            graphs += "min: " + std::to_string(forecast[i]->min_temp_f) + " F\n";
            graphs += "avg: " + std::to_string(forecast[i]->avg_temp_f) + " F\n";
        }

        graphs += "\n";
        graphs += RED + std::string(60, '-') + RESET + "\n";

    }
    return graphs;
}
std::string graph::get_precip_graph(const std::vector<std::shared_ptr<weather::Forecast>> &forecast, const std::string &title, Settings &settings) {
    size_t days = settings.days;
    if (settings.days > forecast.size()) {
        std::cout << YELLOW << "Warning: " << RESET << "days to display is greater than days in forecast" << std::endl;
        std::cout << "Displaying all available days" << std::endl;
        days = forecast.size();
    }
    std::string graphs;
    graphs += RED + std::string(60, '-') + RESET + "\n";


    for (size_t i = 0; i < days; i++) {
        graphs += "Day " + std::to_string(i + 1) + "\n";
        graphs += "Precipitation (um)\n";

        std::vector<int> scaledprecip;
        for (auto &sample: forecast[i]->samples) {
            scaledprecip.push_back(sample->precip_mm * 10);
        }

        graphs += generate_graph(scaledprecip, title);
        graphs += "\n";

        if (settings.celsius) {
            graphs += "max: " + std::to_string(forecast[i]->max_temp_c) + " C\n";
            graphs += "min: " + std::to_string(forecast[i]->min_temp_c) + " C\n";
            graphs += "avg: " + std::to_string(forecast[i]->avg_temp_c) + " C\n";
        } else {
            graphs += "max: " + std::to_string(forecast[i]->max_temp_f) + " F\n";
            graphs += "min: " + std::to_string(forecast[i]->min_temp_f) + " F\n";
            graphs += "avg: " + std::to_string(forecast[i]->avg_temp_f) + " F\n";
        }
        graphs += "\n";
        graphs += "Total precip: " + std::to_string(forecast[i]->total_precip_mm) + " mm\n";

        graphs += "\n";
        graphs += RED + std::string(60, '-') + RESET + "\n";

    }
    return graphs;
}


