cmake_minimum_required(VERSION 3.12)
project(OfflinePlotting)

set(CMAKE_CXX_STANDARD 17)

find_package(ROOT REQUIRED)

include(${ROOT_USE_FILE})
include_directories(jsoncpp/include jsoncpp/include/json)
link_directories(jsoncpp/src jsoncpp/src/lib_json)
subdirs(jsoncpp)

add_executable(OfflinePlotting main.cpp TreeAccess.cpp jsoncpp/src/lib_json/json_reader.cpp jsoncpp/src/lib_json/json_value.cpp jsoncpp/src/lib_json/json_writer.cpp)
target_link_libraries(OfflinePlotting ${ROOT_LIBRARIES} Core Tree Hist)