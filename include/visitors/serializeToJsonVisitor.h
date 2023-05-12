//
// Created by rc_marty on 8.5.23.
//

#pragma once

#include "weather/AirQuality.h"
#include "weather/Astronomy.h"
#include "weather/Forecast.h"
#include "weather/WeatherMoment.h"

using json = nlohmann::json;


namespace Visitors {

    class Visitor {
    public:
        virtual void visit(const struct weather::AirQuality *value) = 0;
        virtual void visit(const struct weather::WeatherMoment *value) = 0;
        virtual void visit(const struct weather::Astronomy *value) = 0;
        virtual void visit(const struct weather::Forecast *value) = 0;
    };

    class SerializeToJsonVisitor : public Visitor {
    private:
        json _jsonValue;
    public:
        void visit(const struct weather::AirQuality *value) override;
        void visit(const struct weather::WeatherMoment *value) override;
        void visit(const struct weather::Astronomy *value) override;
        void visit(const struct weather::Forecast *value) override;

        json serialize() const;
    };
}
