#include <robotarm/serial_transport.hpp>

#include <fcntl.h>
#include <unistd.h>

namespace robotarm {

SerialTransport::SerialTransport(const std::string& pathName) {

    fd_ = open(pathName.c_str(), O_RDWR | O_NOCTTY);

}

SerialTransport::~SerialTransport() {

    close(fd_);
}

bool SerialTransport::write(const std::vector<uint8_t>& data) {

    ssize_t geschrieben = ::write(fd_, data.data(), data.size());

    return (geschrieben == data.size());
    
}

std::vector<uint8_t> SerialTransport::read(size_t count, int timeout_ms) {


    std::vector<uint8_t> puffer(count);

    ssize_t gelesen = ::read(fd_, puffer.data(), count);

    if (gelesen < 0) {return {};}
    
    puffer.resize(gelesen);
    return puffer;
    
}


}