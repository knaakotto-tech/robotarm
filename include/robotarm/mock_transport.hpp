#pragma once

#include <robotarm/transport.hpp>
#include <cstdio>

namespace robotarm {

class MockTransport : public Transport {
public:
    bool write(const std::vector<uint8_t>& data) override {
        std::printf("TX: ");
        for (uint8_t b : data) {
            std::printf("%02X ", b);
        }
        std::printf("\n");
        return true;
    }

    std::vector<uint8_t> read(size_t count, int timeout_ms) override {
        return antwort_;
    }

    void setzeAntwort(const std::vector<uint8_t>& bytes) {
        antwort_ = bytes;
    }

private:
    std::vector<uint8_t> antwort_;



};


}  // namespace robotarm