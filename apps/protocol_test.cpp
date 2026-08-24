#include <robotarm/protocol.hpp>
#include <cstdio>

int main() {

    std::vector<uint8_t> daten = {0x01, 0x02, 0x01};

    uint8_t wert = robotarm::checksum(daten);

    printf("%02X\n", wert);


    return 0;

}