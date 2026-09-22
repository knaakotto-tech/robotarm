#include <robotarm/registers.hpp>
#include <robotarm/protocol.hpp>
#include <robotarm/serial_transport.hpp>
#include <robotarm/servo_bus.hpp>
#include <iostream>
#include <cstdio>
#include <chrono>
#include <thread>


//für er eignis feststellung für die while schliefe zu beenden
#include <poll.h>
#include <unistd.h>




int main(int argc, char* argv[]){

    if(argc < 3){return 1;}

    pollfd tastatur{};
    tastatur.fd = STDIN_FILENO;   // welcher Deskriptor
    tastatur.events = POLLIN;     // was dich interessiert: "gibt es was zu lesen?"

    int ereignis = poll(&tastatur, 1 ,0);

    int id_servo = std::atoi(argv[2]);

    robotarm::SerialTransport serial(argv[1]);
    robotarm::ServoBus bus(serial);

    int max = 0;
    int min = 4096;

    bus.write_register(id_servo, robotarm::R_TORQUE_ENABLE, {0});

    while(ereignis == 0) {
        //Schaut ob etwas sich am ereignis geändert hat (tastendruck)
        ereignis = poll(&tastatur, 1 ,0);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        
        robotarm::Response r = bus.read_register(id_servo, robotarm::R_PRESENT_POSITION);

        if(r.data.size() < 2 || r.valid == false){continue;}
        
        if(max < robotarm::to_uint16(r.data[0], r.data[1])){max = robotarm::to_uint16(r.data[0], r.data[1]);}
        if(min > robotarm::to_uint16(r.data[0], r.data[1])){min = robotarm::to_uint16(r.data[0], r.data[1]);}

        printf("\rServo %d:Max ticks: %4d - Min ticks: %4d", id_servo ,max, min);
        fflush(stdout);
        
    }

    printf("\n");

    return 0;
}
