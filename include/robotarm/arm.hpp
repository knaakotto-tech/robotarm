#pragma once

#include <cstdint> 
#include <vector>
#include <robotarm/servo_bus.hpp>




namespace robotarm{

enum class Status : int8_t{
    jammed,
    done,
    close
};


struct MoveResult{
    Status status = Status::jammed;
    uint8_t servo_id = 0;
    uint16_t position_ticks = 0;
    
};

struct Target{
    uint8_t servo_id = 0;
    float position_degrees = 0.0f;
};

class Arm{

public:
    Arm(ServoBus& servobus) : servobus_(servobus) {}

    MoveResult move_stage(const std::vector<Target>& targets);
    MoveResult go_to_rest();
    bool halt_all();
    


private:
    ServoBus& servobus_;


};


}