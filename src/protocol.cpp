#include <robotarm/protocol.hpp>



namespace robotarm {

uint8_t checksum(const std::vector<uint8_t>& bytes) {
    
    uint8_t sum = 0;

    for (uint8_t b : bytes) {
       
        sum = sum + b;
        
    }

    return ~sum;

}



std::vector<uint8_t> build_packet(uint8_t id, uint8_t instruction, const std::vector<uint8_t>& params) {

    std::vector<uint8_t> body;

    uint8_t length = params.size() + 2;

    body.push_back(id);
    body.push_back(length);
    body.push_back(instruction);
    body.insert(body.end(), params.begin(), params.end());
    

    std::vector<uint8_t> result;
    result.push_back(0xFF);
    result.push_back(0xFF);
    result.insert(result.end(), body.begin(), body.end());
    uint8_t sum = checksum(body);
    result.push_back(sum);

    return result;
}

Response parse_response(const std::vector<uint8_t>& rew) {

    Response r;

    r.id = rew[2];
    r.error = rew[4];
    r.data.insert(r.data.end(), rew.begin() + 5, rew.begin() + 5 + rew[3]-2);

    std::vector<uint8_t> body;

    body.insert(body.end(), rew.begin() + 2, rew.end() -1);

    r.valid = (rew.back() == checksum(body));


    return r;
}

}