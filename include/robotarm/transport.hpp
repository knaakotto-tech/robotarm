#pragma once

#include <vector>
#include <cstdint>


namespace robotarm {

class Transport {
    public:
        virtual ~Transport() = default;

        // Gibt zurueck, was innerhalb der Frist ankam - auch weniger als count.
        // Aufrufer prueft .size(). Leerer Vector = keine Antwort.  
        virtual bool write(const std::vector<uint8_t>& data) = 0;

        virtual std::vector<uint8_t> read(size_t count, int timeout_ms) = 0;
               
};

}