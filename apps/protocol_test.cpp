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

    std::vector<uint8_t> antwort = {0xFF, 0xFF, 0x01, 0x04, 0x00, 0x08, 0xF2};
    robotarm::Response r = robotarm::parse_response(antwort);
    printf("id=%02X error=%02X data=%zu valid=%d\n", r.id, r.error, r.data.size(), r.valid);
    std::vector<uint8_t> lese_antwort = {0x00, 0x08};
    for (uint8_t b : robotarm::build_packet(0x01, 0x00, lese_antwort)) {
        printf("%02X ", b);
    }
    printf("\n");
    return 0;

}