////
//// Created by rc_marty on 8.5.23.
////
//
//#include "visitors/serializeToJsonVisitor.h"
//
//void Visitors::SerializeToJsonVisitor::visit(const weather::AirQuality *value) {
//    _jsonValue["co"] = value->co;
//    _jsonValue["no2"] = value->no2;
//    _jsonValue["o3"] = value->o3;
//    _jsonValue["so2"] = value->so2;
//}
//
//void Visitors::SerializeToJsonVisitor::visit(const struct weather::Forecast *value) {
//    _jsonValue["time"] = value->time;
//    _jsonValue["max_temp_c"] = value->max_temp_c;
//    _jsonValue["min_temp_c"] = value->min_temp_c;
//    _jsonValue["avg_temp_c"] = value->avg_temp_c;
//    _jsonValue["max_temp_f"] = value->max_temp_f;
//    _jsonValue["min_temp_f"] = value->min_temp_f;
//    _jsonValue["avg_temp_f"] = value->avg_temp_f;
//    _jsonValue["max_wind_kph"] = value->max_wind_kph;
//    _jsonValue["total_precip_mm"] = value->total_precip_mm;
//    _jsonValue["condition_text"] = value->condition_text;
//    if (value->air_quality) {
//        _jsonValue["air_quality"] = json::object();
//        value->air_quality->accept(*this);
//    }
//    if (value->astronomy) {
//        _jsonValue["astronomy"] = json::object();
//        value->astronomy->accept(*this);
//    }
//    _jsonValue["samples"] = json::array();
//    for (auto &sample: value->samples) {
//        _jsonValue["samples"].push_back(json::object());
//        sample->accept(*this);
//
//    }
//}
//
//void Visitors::SerializeToJsonVisitor::visit(const weather::WeatherMoment *value) {
//    _jsonValue["time"] = value->time;
//    _jsonValue["temp_c"] = value->temp_c;
//    _jsonValue["temp_f"] = value->temp_f;
//    _jsonValue["feelslike_c"] = value->feelslike_c;
//    _jsonValue["feelslike_f"] = value->feelslike_f;
//    _jsonValue["wind_kph"] = value->wind_kph;
//    _jsonValue["wind_degree"] = value->wind_degree;
//    _jsonValue["pressure_mb"] = value->pressure_mb;
//    _jsonValue["precip_mm"] = value->precip_mm;
//    _jsonValue["humidity"] = value->humidity;
//    _jsonValue["uv"] = value->uv;
//    _jsonValue["condition_text"] = value->condition_text;
//
//    if (value->air_quality) {
//        _jsonValue["air_quality"] = json::object();
//        value->air_quality->accept(*this);
//    }
//    if (value->astronomy) {
//        _jsonValue["astronomy"] = json::object();
//        value->astronomy->accept(*this);
//    }
//}
//
//void Visitors::SerializeToJsonVisitor::visit(const weather::Astronomy *value) {
//    _jsonValue["sunrise"] = value->sunrise;
//    _jsonValue["sunset"] = value->sunset;
//    _jsonValue["moonrise"] = value->moonrise;
//    _jsonValue["moonset"] = value->moonset;
//    _jsonValue["moon_phase"] = value->moon_phase;
//    _jsonValue["moon_illumination"] = value->moon_illumination;
//}
//
//json Visitors::SerializeToJsonVisitor::serialize() const {
//    return _jsonValue;
//}