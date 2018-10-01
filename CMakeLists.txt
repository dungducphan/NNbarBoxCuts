cmake_minimum_required(VERSION 3.12)
project(OfflinePlotting)

set(CMAKE_CXX_STANDARD 17)

find_package(ROOT REQUIRED)

include(${ROOT_USE_FILE})

add_executable(OfflinePlotting main.cpp TreeAccess.cpp kNN.cpp kNN.h)
target_link_libraries(OfflinePlotting ${ROOT_LIBRARIES} Core Tree Hist)