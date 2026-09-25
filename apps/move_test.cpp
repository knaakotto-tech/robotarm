#include <robotarm/servo_bus.hpp>
#include <robotarm/protocol.hpp>
#include <robotarm/serial_transport.hpp>
#include <robotarm/registers.hpp>
#include <cstdio>
#include <thread>
#include <chrono>
#include <robotarm/arm_config.hpp>
#include <poll.h>
#include <unistd.h>
#include <robotarm/joint.hpp>



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


void set_print_position(uint8_t winkel, robotarm::ServoBus& bus, int id_eingabe){
    
    robotarm::Response r = bus.read_register(id_eingabe, robotarm::R_PRESENT_POSITION);

    print_read(r);

    const robotarm::Joint& joint = robotarm::joint_by_id(id_eingabe);

    robotarm::TickResult ziel = robotarm::degrees_to_ticks(joint, winkel);

    if(!ziel.valid){
        printf("Winkel %.1f ligt nicht in den voegeschirebeden grenzen von gelenk %d\n", winkel, joint.servo_id);
        return;
    }

    bus.write_register(id_eingabe, robotarm::R_GOAL_POSITION, robotarm::to_low_high(ziel.ticks));
    std::this_thread::sleep_for(std::chrono::milliseconds(400));

    bool position_ready = true;

    //notfall tastedrücke und es bricht die schleife ab
    pollfd tastatur{};
    tastatur.fd = STDIN_FILENO;
    tastatur.events = POLLIN;

    while(position_ready){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        r = bus.read_register(id_eingabe, robotarm::R_PRESENT_POSITION);

        int tasten_druck = poll(&tastatur, 1, 0);

        if(tasten_druck > 0){
            printf("Tastendruck erkannt, winkel: %d wurde abgebrochen", winkel);
            position_ready = false;
        }

        if (r.valid == false){continue;}

        if(robotarm::to_uint16(r.data[0], r.data[1]) == winkel || tasten_druck > 0){position_ready = false;}


        

    }
    return print_read(r);

}


int main(int argc, char* argv[]) {

    if(argc < 3){
        printf("Fehler beim port aufrufen: %s", argv[0]);
        return 1;
    }

    robotarm::SerialTransport serial(argv[1]);
    robotarm::ServoBus bus(serial);


    int id_eingabe = std::atoi(argv[2]);

    robotarm::joint_by_id(id_eingabe);

    bus.write_register(id_eingabe, robotarm::R_GOAL_SPEED, robotarm::to_low_high(100));
    bus.write_register(id_eingabe, robotarm::R_ACCELERATION, {50});


    set_print_position(20, bus, id_eingabe);

    set_print_position(0, bus, id_eingabe);

    set_print_position(-20, bus, id_eingabe);


}