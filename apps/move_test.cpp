#include <robotarm/servo_bus.hpp>
#include <robotarm/protocol.hpp>
#include <robotarm/serial_transport.hpp>
#include <robotarm/registers.hpp>
#include <cstdio>


int main() {

    robotarm::SerialTransport serial("/dev/ttyACM0");
    robotarm::ServoBus bus(serial);

    robotarm::Response r = bus.write_register(1, robotarm::R_TORQUE_ENABLE, {1});
    std::printf("valid=%d error=%02X\n", r.valid, r.error);

}