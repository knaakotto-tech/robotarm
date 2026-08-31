#include <robotarm/mock_transport.hpp>
#include <robotarm/servo_bus.hpp>
#include <robotarm/registers.hpp>

int main() {

    robotarm::MockTransport mock;
    robotarm::ServoBus bus(mock);

    mock.setzeAntwort({0xFF, 0xFF, 0x01, 0x02, 0x00, 0xFC});
    robotarm::Response r = bus.write_register(1, robotarm::R_TORQUE_ENABLE, {1}); 

    std::printf("valid=%d error=%02X\n", r.valid, r.error);

    return 0;
}