#include <robotarm/protocol.hpp>
#include <cstdio>

int main() {

    std::vector<uint8_t> daten = {0x01, 0x02, 0x01};

    uint8_t wert = robotarm::checksum(daten);

    printf("%02X\n", wert);



    std::vector<uint8_t> schreibe_parameter = {0x05, 0x02};


    for (uint8_t b : robotarm::build_packet(0x01, 0x03, schreibe_parameter)) {
        printf("%02X ", b);
        
    }

    printf("\n");

    return 0;

}