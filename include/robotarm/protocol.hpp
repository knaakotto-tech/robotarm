#pragma once

#include <vector>
#include <cstdint>


namespace robotarm {

uint8_t checksum(const std::vector<uint8_t>& bytes);


}