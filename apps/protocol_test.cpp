#include <robotarm/protocol.hpp>
#include <cstdio>
#include <robotarm/registers.hpp>

int main() {
/*
    std::vector<uint8_t> daten = {0x01, 0x02, 0x01};

    uint8_t wert = robotarm::checksum(daten);

    printf("%02X\n", wert);



    std::vector<uint8_t> schreibe_parameter = {0x05, 0x02};


    for (uint8_t b : robotarm::build_packet(0x01, 0x03, schreibe_parameter)) {
        printf("%02X ", b);
        
    }

    printf("\n");
*/
    std::vector<uint8_t> antwort = {0xFF, 0xFF, 0x01, 0x04, 0x00, 0x00, 0x08, 0xF1};
    robotarm::Response r = robotarm::parse_response(antwort);
    printf("id=%02X error=%02X data=%zu valid=%d\n", r.id, r.error, r.data.size(), r.valid);
    std::vector<uint8_t> lese_antwort = {0x00, 0x08};
    for (uint8_t b : robotarm::build_packet(0x01, 0x00, lese_antwort)) {
        printf("%02X ", b);
    }
    printf("\n");


    /*
    std::vector<uint8_t> lesenParamenter = {robotarm::R_PRESENT_POSITION, 2}; 

    for (uint8_t b : robotarm::build_packet(0x01, 0x02, lesenParamenter)) {
        printf("%02X ", b);
    }
    printf("\n");
    
    printf("%u\n", robotarm::to_uint16(0xE8, 0x03));

    std::vector<uint8_t> b = robotarm::to_low_high(1000);

    printf("%02X %02X -> %u\n", b[0], b[1], robotarm::to_uint16(b[0], b[1]));
    */
    return 0;

}