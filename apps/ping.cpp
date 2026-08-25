#include <iostream>
#include <cstdio>
#include <robotarm/protocol.hpp>
#include <robotarm/mock_transport.hpp>

int main() {

    robotarm::MockTransport mock;
    
    mock.setzeAntwort({0xFF, 0xFF, 0x01, 0x02, 0x00, 0xFC});

    mock.write(robotarm::build_packet(0x01, 0x01, {}));
    
    std::vector<uint8_t> antwort = mock.read(6, 100);

    robotarm::Response r = robotarm::parse_response(antwort);

    printf("%d", r.valid);

    return 0;
}