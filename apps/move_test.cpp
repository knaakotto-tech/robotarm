#include <robotarm/servo_bus.hpp>
#include <robotarm/protocol.hpp>
#include <robotarm/serial_transport.hpp>
#include <robotarm/registers.hpp>
#include <cstdio>
#include <thread>
#include <chrono>


int main() {

    robotarm::SerialTransport serial("/dev/ttyACM0");
    robotarm::ServoBus bus(serial);

    bus.write_register(1, robotarm::R_TORQUE_ENABLE, {1});
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    bus.write_register(1, robotarm::R_GOAL_POSITION, robotarm::to_low_high(1000));
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    bus.write_register(1, robotarm::R_GOAL_POSITION, robotarm::to_low_high(3000));
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

}