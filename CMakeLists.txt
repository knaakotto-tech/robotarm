cmake_minimum_required(VERSION 3.20)
project(robotarm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ping apps/ping.cpp)
target_include_directories(ping PRIVATE include)