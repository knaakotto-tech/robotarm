#include <robotarm/servo_bus.hpp>
#include <robotarm/serial_transport.hpp>
#include <robotarm/registers.hpp>
#include <robotarm/protocol.hpp>
#include <cstdio>
#include <cstdlib>    // für std::atoi
#include <iostream>   // für std::cin
#include <thread>
#include <chrono>

// print_read aus torque_test hierher kopieren

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

    // 1. argc prüfen: Diesmal brauchst du Port UND ID.
    //    Wenn etwas fehlt: "Aufruf: ./calibrate_middle <port> <id>" ausgeben, return 1
    if(argc < 3){
        printf("Aufruf: %s port id\n", argv[0]);
        return 1;
    }

    // 2. ID aus argv[2] holen:
    int id_eingabe = std::atoi(argv[2]);
    //    Prüfen, ob sie zwischen 1 und 5 liegt, sonst Meldung und return 1.
    //    Erst danach in uint8_t umwandeln.
    if (id_eingabe < 1|| id_eingabe > 5){return 1;}


    // 3. SerialTransport und ServoBus anlegen
    robotarm::SerialTransport serial(argv[1]);
    robotarm::ServoBus bus(serial);


    // 4. Position lesen und ausgeben ("vorher")
    robotarm::Response r = bus.read_register(id_eingabe, robotarm::R_PRESENT_POSITION);
    print_read(r);
    if(r.valid == false){
            printf("ist nicht valid\n");
            return 1;
        }
    // 5. Sicherheitsabfrage: "Servo X steht in der Mitte? Enter zum Kalibrieren"
    //    und mit std::cin.get() warten
    printf("Servo %d steht in der Mitte? Enter zum Kalibrieren", r.id);
    std::cin.get();


    // 6. TORQUE_CALIBRATE_MIDDLE in R_TORQUE_ENABLE schreiben
    //    Die Antwort prüfen: Ist sie valid? Wenn nicht, Meldung und abbrechen.
    
    
    r = bus.write_register(id_eingabe, robotarm::R_TORQUE_ENABLE, {robotarm::TORQUE_CALIBRATE_MIDDLE});
    
     if (!r.valid) {
        printf("Kalibrierbefehl nicht bestaetigt\n");
        return 1;
    }
    printf("Kalibrierbefehl bestaetigt\n");

    // 7. Kurz warten (100 ms)
    std::this_thread::sleep_for (std::chrono::milliseconds(100));
    // 8. Position lesen und ausgeben ("nachher", sollte etwa 2048 sein)
    r = bus.read_register(id_eingabe, robotarm::R_PRESENT_POSITION);
    print_read(r);
    // 9. Torque auf 0 schreiben
    bus.write_register(id_eingabe, robotarm::R_TORQUE_ENABLE, {0});
}