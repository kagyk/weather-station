cmake_minimum_required(VERSION 3.5)

project(weather_station LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_BUILD_TYPE Release)


find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
get_target_property(QtCore_location Qt5::Core LOCATION)
set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "DEBUG_CONFIGURATIONS")


set(TS_FILES weather_station_ru_RU.ts)
set(CONF_FILE config_writer/conf/config.xml)
set(CONFIG_FILE_DEST "${CMAKE_BINARY_DIR}/conf/config.xml")
set(SCRIPT_FILE script/sensors.sh)
set(SCRIPT_FILE_DEST "${CMAKE_BINARY_DIR}/script/sensors.sh")

add_executable(weather_station
    main.cpp
    WeatherStationWindows.cpp
    WeatherStationWindows.h
    WeatherStationWindows.ui
    config_writer/Config.cpp
    config_writer/Config.h
    clocks/Clock.cpp
    clocks/Clock.h
    sensor/SensorController.cpp
    sensor/SensorController.h
    ${TS_FILES}
    ${CONF_FILE}
    ${SCRIPT_FILE}
  )


configure_file("${CONF_FILE}" "${CONFIG_FILE_DEST}" COPYONLY)
configure_file("${SCRIPT_FILE}" "${SCRIPT_FILE_DEST}" COPYONLY)

target_link_libraries(weather_station PRIVATE Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

