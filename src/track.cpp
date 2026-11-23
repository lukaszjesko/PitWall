#include "track.h"

#include <fstream>
#include <stdexcept>

Track::Track()
    : name_("Tor Poznań"),
      laps_(30),
      base_lap_(LapTime::fromSeconds(91.5)),
      pit_loss_(LapTime::fromSeconds(21.0)),
      wear_factor_(1.0) {}

Track::Track(const std::string& name, int laps, const LapTime& base_lap,
             const LapTime& pit_loss, double wear_factor)
    : name_(name),
      laps_(laps),
      base_lap_(base_lap),
      pit_loss_(pit_loss),
      wear_factor_(wear_factor) {}

// Plik toru: w pierwszej linii nazwa, potem 4 pary "opis liczba":
// okrążenia, czas okrążenia [s], strata w boksie [s], mnożnik zużycia.
// Gdy pliku nie ma albo coś się nie zgadza, rzuca std::runtime_error.
Track Track::loadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("nie mogę otworzyć pliku " + path);
    }
    std::string name;
    std::getline(file, name);
    if (!name.empty() && name.back() == '\r') {
        name.pop_back();
    }
    std::string label;
    int laps = 0;
    double base_lap = 0.0;
    double pit_loss = 0.0;
    double wear = 0.0;
    file >> label >> laps >> label >> base_lap >> label >> pit_loss >> label
         >> wear;
    if (!file || name.empty()) {
        throw std::runtime_error("zły format pliku " + path);
    }
    if (laps <= 0 || base_lap <= 0.0 || pit_loss < 0.0 || wear <= 0.0) {
        throw std::runtime_error("złe wartości w pliku " + path);
    }
    return Track(name, laps, LapTime::fromSeconds(base_lap),
                 LapTime::fromSeconds(pit_loss), wear);
}

std::string Track::getName() const {
    return name_;
}

int Track::getLaps() const {
    return laps_;
}

LapTime Track::getBaseLap() const {
    return base_lap_;
}

LapTime Track::getPitLoss() const {
    return pit_loss_;
}

double Track::getWearFactor() const {
    return wear_factor_;
}
