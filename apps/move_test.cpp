#include <robotarm/servo_bus.hpp>
#include <robotarm/protocol.hpp>
#include <robotarm/serial_transport.hpp>
#include <robotarm/registers.hpp>
#include <cstdio>
#include <thread>
#include <chrono>

void print_read(const robotarm::Response& r) {
    
    if(r.valid == true) {
        printf("valid=%d station=", r.valid);
        for(uint8_t b : r.data){
            printf("%02X", b);
        }
    } else{
        printf("unvollsänding => %d ", r.valid);

        std::printf("RX: %zu Bytes\n", r.data.size()); 

    }

    printf("\n");
}



int main() {

    robotarm::SerialTransport serial("/dev/ttyACM0");
    robotarm::ServoBus bus(serial);

    bus.write_register(1, robotarm::R_TORQUE_ENABLE, {1});
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    robotarm::Response r = bus.read_register(1, robotarm::R_PRESENT_POSITION, 2);
    
    print_read(r);


    bus.write_register(1, robotarm::R_GOAL_POSITION, robotarm::to_low_high(1000));
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));


    r = bus.read_register(1, robotarm::R_PRESENT_POSITION, 2);

    print_read(r);

    bus.write_register(1, robotarm::R_GOAL_POSITION, robotarm::to_low_high(3000));
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));


    r = bus.read_register(1, robotarm::R_PRESENT_POSITION, 2);
   print_read(r);

}