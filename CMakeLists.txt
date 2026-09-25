cmake_minimum_required(VERSION 3.20)
project(robotarm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)

add_executable(ping apps/ping.cpp src/serial_transport.cpp src/protocol.cpp)
target_include_directories(ping PRIVATE include)


add_executable(mock_test apps/mock_test.cpp)
target_include_directories(mock_test PRIVATE include)

add_executable(protocol_test apps/protocol_test.cpp src/protocol.cpp src/joint.cpp)
target_include_directories(protocol_test PRIVATE include)

add_executable(bus_test apps/bus_test.cpp src/servo_bus.cpp src/protocol.cpp)
target_include_directories(bus_test PRIVATE include)

add_executable(move_test apps/move_test.cpp src/servo_bus.cpp src/serial_transport.cpp src/protocol.cpp src/joint.cpp)
target_include_directories(move_test PRIVATE include)

add_executable(torque_test apps/torque_test.cpp src/servo_bus.cpp src/serial_transport.cpp src/protocol.cpp)
target_include_directories(torque_test PRIVATE include)

add_executable(calibrate_middle apps/calibrate_middle.cpp src/servo_bus.cpp src/serial_transport.cpp src/protocol.cpp)
target_include_directories(calibrate_middle PRIVATE include)

add_executable(measure_limits apps/measure_limits.cpp src/servo_bus.cpp src/serial_transport.cpp src/protocol.cpp)
target_include_directories(measure_limits PRIVATE include)