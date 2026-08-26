#pragma once

#include <cstdint>


namespace robotarm {

//1 byte
constexpr uint8_t R_TORQUE_ENABLE = 40;
//1 byte
constexpr uint8_t R_ACCELERATION = 41;
//2 byte
constexpr uint8_t R_GOAL_POSITION = 42;
//2 byte
constexpr uint8_t R_GOAL_SPEED = 46;


//2 byte
constexpr uint8_t R_PRESENT_POSITION = 56;
// 2byte
constexpr uint8_t R_PRESENT_SPEED = 58;

//2 byte
constexpr uint8_t R_PRESENT_LOAD = 60;
//1 byte
constexpr uint8_t R_PRESENT_VOLTAGE = 62;
//1 byte
constexpr uint8_t R_PRESENT_TEMPERATURE = 63;
//1 byte
constexpr uint8_t R_SERVO_STATUS = 65;


}



