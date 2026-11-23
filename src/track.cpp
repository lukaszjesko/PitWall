#include "track.h"

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
