cmake_minimum_required(VERSION 3.20)
project(robotarm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ping apps/ping.cpp src/serial_transport.cpp)
target_include_directories(ping PRIVATE include)


add_executable(mock_test apps/mock_test.cpp)
target_include_directories(mock_test PRIVATE include)

add_executable(protocol_test apps/protocol_test.cpp src/protocol.cpp)
target_include_directories(protocol_test PRIVATE include)

