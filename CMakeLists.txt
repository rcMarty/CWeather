cmake_minimum_required(VERSION 3.8)
project(CWeather)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")


if (NOT DISABLE_ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif ()

add_compile_options(-Wall -Wextra -pedantic)

include_directories(include)
include_directories(include/3rdparty)

add_executable(CWeather src/main.cpp src/io.cpp include/queryBuilder.h src/queryBuilder.cpp src/weather/Forecast.cpp include/weather/Forecast.h src/weather/WeatherMoment.cpp include/weather/WeatherMoment.h src/weather/AirQuality.cpp include/weather/AirQuality.h src/weather/Astronomy.cpp include/weather/Astronomy.h src/settings.cpp include/settings.h include/parsersJson/AirQualityJson.h include/parsersJson/AstronomyJson.h include/parsersJson/ForecastJson.h include/parsersJson/WeatherMomentJson.h)
target_link_libraries(CWeather curlpp curl)

