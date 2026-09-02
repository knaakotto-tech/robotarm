#include <robotarm/servo_bus.hpp>
#include <vector>
#include <cstdio>

namespace robotarm {

Response ServoBus::write_register(uint8_t id, Register reg, const std::vector<uint8_t>& werte) {

    //sicherheit das nicht zu viele oder zu wenig Daten über geben werden
    if (werte.size() != reg.width) {
        Response r;
        fprintf(stderr, "Falsche Werte übergeben, erwartet = %d Anzahl erhaltener Werte = %zu\n", static_cast<int>(reg.width), werte.size());
        return r;
    }

    std::vector<uint8_t> params;

    params.push_back(reg.address);
    params.insert(params.end(), werte.begin(), werte.end());


    std::vector<uint8_t> paket = build_packet(id, 0x03, params);

    transport_.write(paket);

    std::vector<uint8_t> antwort = transport_.read(6, 100);

    return parse_response(antwort);


}

Response ServoBus::read_register(uint8_t id, Register reg) {

    std::vector<uint8_t> param;
    param.push_back(reg.address);
    param.push_back(reg.width);

    std::vector<uint8_t> pack = build_packet(id, 0x02, param);

    transport_.write(pack);

    uint8_t antwort_laenge = 6 + reg.width;

    return parse_response(transport_.read(antwort_laenge, 100));


}

}