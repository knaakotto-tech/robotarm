cmake_minimum_required(VERSION 3.20)
project(robotarm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)

add_library(robotarm src/servo_bus.cpp src/serial_transport.cpp src/protocol.cpp src/joint.cpp src/arm.cpp)
target_include_directories(robotarm PUBLIC include)


add_executable(ping apps/ping.cpp)
target_link_libraries(ping PRIVATE robotarm)


add_executable(mock_test apps/mock_test.cpp)
target_link_libraries(mock_test PRIVATE robotarm)

add_executable(protocol_test apps/protocol_test.cpp )
target_link_libraries(protocol_test PRIVATE robotarm)

add_executable(bus_test apps/bus_test.cpp)
target_link_libraries(bus_test PRIVATE robotarm)

add_executable(move_test apps/move_test.cpp)
target_link_libraries(move_test PRIVATE robotarm)

add_executable(torque_test apps/torque_test.cpp)
target_link_libraries(torque_test PRIVATE robotarm)

add_executable(calibrate_middle apps/calibrate_middle.cpp)
target_link_libraries(calibrate_middle PRIVATE robotarm)

add_executable(measure_limits apps/measure_limits.cpp)
target_link_libraries(measure_limits PRIVATE robotarm)