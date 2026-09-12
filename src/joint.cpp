#include <robotarm/joint.hpp>
#include <cmath>

namespace robotarm {

TickResult degrees_to_ticks(const Joint& joint, float degrees) {

    TickResult result;

    if (degrees > joint.max_degrees || degrees < joint.min_degrees) {
        return result;
    }

    int32_t offset = std::lround(static_cast<int>(joint.direction) * degrees * TICKS_PER_DEGREE);
    
    int32_t position = offset + joint.zero_ticks;

    

    if (position >= 0 && position <= 4095) {
        result.ticks = static_cast<int16_t>(position);
        result.valid = true;
        return result;

    }

    return result;
}

float ticks_to_degrees(const Joint& joint, uint16_t ticks) {

    float winkel = ((static_cast<int32_t>(ticks) - static_cast<int32_t>(joint.zero_ticks)) * DEGREE_PER_TICK) * static_cast<int>(joint.direction);
    return winkel;
}




}