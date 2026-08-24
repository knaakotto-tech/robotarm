#include <robotarm/protocol.hpp>



namespace robotarm {

uint8_t checksum(const std::vector<uint8_t>& bytes) {
    
    uint8_t sum = 0;

    for (uint8_t b : bytes) {
       
        sum = sum + b;
        
    }

    return ~sum;

}


}