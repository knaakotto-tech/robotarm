#include <robotarm/mock_transport.hpp>

int main() {

    robotarm::MockTransport mock;

    mock.write({0xFF, 0xFF, 0x01, 0x02, 0x01, 0xFB});

    mock.setzeAntwort({0xFF, 0xFF, 0x01, 0x02, 0x00, 0xFC});
    std::vector<uint8_t> antwort = mock.read(6, 100);

    std::printf("RX: %zu Bytes\n", antwort.size());


}