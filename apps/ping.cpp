#include <cstdio>
#include <stdexcept>
#include <robotarm/protocol.hpp>
#include <robotarm/serial_transport.hpp>

int main() {
    try {
        robotarm::SerialTransport t("/dev/ttyACM0");
        

        t.write(robotarm::build_packet(0x01, 0x01, {}));
        
        std::vector<uint8_t> antwort = t.read(6, 100);

        robotarm::Response r = robotarm::parse_response(antwort);

        printf("%d", r.valid);
    }
    catch (const std::runtime_error& e){
        printf("Fehler: %s\n", e.what());
        return 1;
    }
    return 0;
}