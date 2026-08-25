#pragma once

#include <robotarm/transport.hpp>
#include <string>


namespace robotarm {

class SerialTransport : public Transport {
    public:
        SerialTransport(const std::string& pathName);
        ~SerialTransport();

        
        bool write (const std::vector<uint8_t>& data) override;
        std::vector<uint8_t> read(size_t count, int timeout_ms) override;

      

    private:
        int fd_; 

};



}