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

add_executable(CWeather src/main.cpp src/io.cpp src/queryBuilder.cpp src/weather/Forecast.cpp src/weather/WeatherMoment.cpp src/weather/AirQuality.cpp src/weather/Astronomy.cpp src/settings.cpp src/visitors/SerializeToJsonVisitor.cpp)
target_link_libraries(CWeather curlpp curl)

