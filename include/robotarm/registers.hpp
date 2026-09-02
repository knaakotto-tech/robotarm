#pragma once

#include <vector>
#include <cstdint>


namespace robotarm {


struct Register {
    uint8_t address;
    uint8_t width;
};


constexpr Register R_TORQUE_ENABLE = {.address = 40, .width = 1};

constexpr Register R_ACCELERATION = {.address = 41, .width = 1};

constexpr Register R_GOAL_POSITION = {.address = 42, .width = 2};

constexpr Register R_GOAL_SPEED = {.address = 46, .width = 2};



constexpr Register R_PRESENT_POSITION = {.address = 56, .width = 2};
// 2byte
constexpr Register R_PRESENT_SPEED = {.address = 58, .width = 2};


constexpr Register R_PRESENT_LOAD = {.address = 60, .width = 2};

constexpr Register R_PRESENT_VOLTAGE = {.address = 62, .width = 1};

constexpr Register R_PRESENT_TEMPERATURE = {.address = 63, .width = 1};

constexpr Register R_SERVO_STATUS = {.address = 65, .width = 1};

}



