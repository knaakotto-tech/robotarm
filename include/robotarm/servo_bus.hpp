#pragma once 

#include <robotarm/transport.hpp>
#include <robotarm/protocol.hpp>

namespace robotarm {

class ServoBus {

public:
    ServoBus(Transport& transport) : transport_(transport) {}

    Response write_register(uint8_t id, uint8_t adresse, const std::vector<uint8_t>& werte);    


private:
    Transport& transport_;

};



}