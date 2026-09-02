#pragma once 

#include <robotarm/transport.hpp>
#include <robotarm/protocol.hpp>
#include <robotarm/registers.hpp>

namespace robotarm {

class ServoBus {

public:
    ServoBus(Transport& transport) : transport_(transport) {}

    Response write_register(uint8_t id, Register adresse, const std::vector<uint8_t>& werte);  
    
    Response read_register(uint8_t id, Register adresse);


private:
    Transport& transport_;

};



}