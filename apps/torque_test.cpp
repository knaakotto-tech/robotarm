#include <robotarm/servo_bus.hpp>
#include <robotarm/serial_transport.hpp>
#include <robotarm/registers.hpp>
#include <robotarm/protocol.hpp>
#include <cstdio>
#include <iostream>
#include <thread>
#include <chrono>

void print_read(const robotarm::Response& r) {
    
    if(r.valid == true && r.data.size() >= 2) {
        printf("Ticks = %u", robotarm::to_uint16(r.data[0], r.data[1]));
    } else{
        printf("unvollsänding => %d ", r.valid);

        std::printf("RX: %zu Bytes\n", r.data.size()); 

    }

    printf("\n");
}



int main(int argc, char* argv[]) {

    // 1. argc pruefen, sonst Hinweis ausgeben und return 1
    if (argc < 2) {return 1;}


    // 2. SerialTransport(argv[1]) und ServoBus anlegen
    robotarm::SerialTransport serial(argv[1]);
    robotarm::ServoBus bus(serial);


    // 3. Torque an: write_register(1, R_TORQUE_ENABLE, {1})
    bus.write_register(1, robotarm::R_TORQUE_ENABLE, {1});
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // 4. Position lesen und ausgeben
    robotarm::Response r = bus.read_register(1, robotarm::R_PRESENT_POSITION);
    print_read(r);

    // 5. Torque aus: {0}
    bus.write_register(1, robotarm::R_TORQUE_ENABLE, {0});
    std::this_thread::sleep_for(std::chrono::milliseconds(100));


    // 6. "Servo von Hand drehen, dann Enter" + std::cin.get()
    printf("Enterdrücken wenn position gelesen werden soll\n");
    std::cin.get();
    

    // 7. Position nochmal lesen und ausgeben
    r = bus.read_register(1, robotarm::R_PRESENT_POSITION);
    print_read(r);

}