#pragma once

#include <vector>
#include <cstdint>


namespace robotarm {

struct Response {
    uint8_t id;
    uint8_t error;
    std::vector<uint8_t> data;
    bool valid; 

};

Response parse_response(const std::vector<uint8_t>& rew);

uint8_t checksum(const std::vector<uint8_t>& bytes);

std::vector<uint8_t> build_packet(uint8_t id, uint8_t instruction, const std::vector<uint8_t>& params);

uint16_t to_uint16(uint8_t lowByte, uint8_t highByte);

std::vector<uint8_t> to_low_high(uint16_t wert);

}