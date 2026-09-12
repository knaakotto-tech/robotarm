#pragma once

#include <cstdint>

namespace robotarm {

enum class Direction : int8_t {
    normal = 1,
    inverted = -1
};

struct Joint {
    uint8_t servo_id;
    uint16_t zero_ticks;
    Direction direction;
    float min_degrees;
    float max_degrees;
    
};  

constexpr float TICKS_PER_DEGREE = 4096.0f / 360.0f;
constexpr float DEGREE_PER_TICK = 360.0f / 4096.0f; 


struct TickResult {
    uint16_t ticks = 0;
    bool valid = false;
};

TickResult degrees_to_ticks(const Joint& joint, float degrees);

float ticks_to_degrees(const Joint& joint, uint16_t ticks);


}