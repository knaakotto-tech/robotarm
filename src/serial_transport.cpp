#include <robotarm/serial_transport.hpp>

#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <termios.h>

namespace robotarm {

SerialTransport::SerialTransport(const std::string& pathName) {
    //Oeffnet den Port 
    fd_ = open(pathName.c_str(), O_RDWR | O_NOCTTY);
    
    //Falls es einen Fehler mit dem Port gibt:
    if (fd_ < 0) {
        throw std::runtime_error("Port lässt sich nicht öffnen; " + pathName);
    }
    struct termios tty;
    //seist den Port zu
    tcgetattr(fd_, &tty);
    //nimmt das orginal
    cfmakeraw(&tty);
    //bestimmt die wartezeit von 0,1 s
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 1;
    
    
    #ifdef __APPLE__
    //macOS Variante weil es bei MacOS nur bis B230400 geht
    #else

    cfsetospeed(&tty, B1000000);
    cfsetispeed(&tty, B1000000);
    #endif
    //gibt alles weiter
    tcsetattr(fd_, TCSANOW, &tty);
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