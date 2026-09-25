#pragma once

#include <robotarm/joint.hpp>
#include <array>
#include <stdexcept>

namespace robotarm {

    //id -1 und so bekommt man seinen richtigen joint 
    constexpr std::array<Joint, 5> JOINTS = {{
        {.servo_id = 1, .zero_ticks = 2048, .direction = Direction::normal, .min_degrees = -30.0f, .max_degrees = 30.0f},
        {.servo_id = 2, .zero_ticks = 2048, .direction = Direction::normal, .min_degrees = -30.0f, .max_degrees = 30.0f},
        {.servo_id = 3, .zero_ticks = 2048, .direction = Direction::normal, .min_degrees = -30.0f, .max_degrees = 30.0f},
        {.servo_id = 4, .zero_ticks = 2048, .direction = Direction::normal, .min_degrees = -30.0f, .max_degrees = 30.0f},
        {.servo_id = 5, .zero_ticks = 2048, .direction = Direction::normal, .min_degrees = -30.0f, .max_degrees = 30.0f}


    }};

    constexpr const Joint& joint_by_id(uint8_t id){
        
        
        if (id < 1 || id > JOINTS.size()){
            throw std::runtime_error("Es gibt keine servo mit dieser ID");
        }
        return JOINTS[id -1];
    }

    //prüft die element in der liste und wenn welche vertauscht sind bricht das programm ab
    static_assert(joint_by_id(1).servo_id == 1, "JOINTS müssen nach servo ID sortiert werden");
    static_assert(joint_by_id(5).servo_id == 5);

}