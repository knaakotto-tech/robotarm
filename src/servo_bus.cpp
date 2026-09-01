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

Response ServoBus::read_register(uint8_t id, uint8_t adresse, uint8_t anzahl) {

    std::vector<uint8_t> param;
    param.push_back(adresse);
    param.push_back(anzahl);

    std::vector<uint8_t> pack = build_packet(id, 0x02, param);

    transport_.write(pack);

    uint8_t antwort_laenge = 6 + anzahl;

    return parse_response(transport_.read(antwort_laenge, 100));


}

}