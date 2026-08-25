#include <robotarm/serial_transport.hpp>

#include <fcntl.h>
#include <unistd.h>

namespace robotarm {

SerialTransport::SerialTransport(const std::string& pathName) {
    //Oeffnet den Port 
    fd_ = open(pathName.c_str(), O_RDWR | O_NOCTTY);

}

SerialTransport::~SerialTransport() {
    //schließt den port wieder 
    close(fd_);
}

bool SerialTransport::write(const std::vector<uint8_t>& data) {

    //speichert die werte zwischen
    ssize_t geschrieben = ::write(fd_, data.data(), data.size());
    //schaut ob alle werte rausgeschickt wurden
    return (geschrieben == data.size());
    
}

std::vector<uint8_t> SerialTransport::read(size_t count, int timeout_ms) {

    //speichert die werte zwischen von der antwort
    std::vector<uint8_t> puffer(count);
    ssize_t gelesen = ::read(fd_, puffer.data(), count);
    
    //fals eine negative zahl zurück kommt 
    //da die goeße ja nicht negativ von der Antwort sein kann
    if (gelesen < 0) {return {};}
    
    puffer.resize(gelesen);
    return puffer;
    
}


}