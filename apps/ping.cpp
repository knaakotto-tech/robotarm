#include <iostream>
#include <cstdio>
#include <robotarm/protocol.hpp>
#include <robotarm/serial_transport.hpp>

int main() {

    robotarm::SerialTransport t("def/ttyACM0");
    

    t.write(robotarm::build_packet(0x01, 0x01, {}));
    
    std::vector<uint8_t> antwort = t.read(6, 100);

    robotarm::Response r = robotarm::parse_response(antwort);

    printf("%d", r.valid);

    return 0;
}