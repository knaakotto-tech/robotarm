#pragma once

#include <vector>
#include <cstdint>


namespace robotarm {

uint8_t checksum(const std::vector<uint8_t>& bytes);

std::vector<uint8_t> build_packet(uint8_t id, uint8_t instruction, const std::vector<uint8_t>& params);

}