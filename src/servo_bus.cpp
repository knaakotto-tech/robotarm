#include <robotarm/servo_bus.hpp>
#include <vector>


namespace robotarm {

Response ServoBus::write_register(uint8_t id, uint8_t adresse, const std::vector<uint8_t>& werte) {

    std::vector<uint8_t> params;

    params.push_back(adresse);
    params.insert(params.end(), werte.begin(), werte.end());


    std::vector<uint8_t> paket = build_packet(id, 0x03, params);

    transport_.write(paket);

    std::vector<uint8_t> antwort = transport_.read(6, 100);

    return parse_response(antwort);


}

}