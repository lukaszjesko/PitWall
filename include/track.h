#ifndef PITWALL_TRACK_H
#define PITWALL_TRACK_H

#include <string>

#include "lap_time.h"

// Tor: liczba okrążeń, czas bazowy, strata w boksie, zużycie opon.
class Track {
public:
    Track();
    Track(const std::string& name, int laps, const LapTime& base_lap,
          const LapTime& pit_loss, double wear_factor);

    static Track loadFromFile(const std::string& path);

    std::string getName() const;
    int getLaps() const;
    LapTime getBaseLap() const;
    LapTime getPitLoss() const;
    double getWearFactor() const;

private:
    std::string name_;
    int laps_;
    LapTime base_lap_;
    LapTime pit_loss_;
    double wear_factor_;
};

#endif
