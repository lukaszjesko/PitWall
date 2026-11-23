#ifndef PITWALL_CAR_H
#define PITWALL_CAR_H

#include <memory>
#include <string>

#include "driver.h"
#include "lap_time.h"
#include "track.h"
#include "tyre.h"

// Samochód zespołu. Ma na własność (kompozycja) kierowcę i oponę.
class Car {
public:
    Car(const std::string& team_name, const Driver& driver, bool is_player);

    void startRace(Compound compound);
    void driveLap(const Track& track);
    void pitStop(Compound compound, const LapTime& time_lost);
    void setDriverSkill(int skill);

    std::string getTeamName() const;
    const Driver& getDriver() const;
    const Tyre& getTyre() const;
    LapTime getTotalTime() const;
    bool isPlayer() const;

private:
    std::string team_name_;
    Driver driver_;
    std::unique_ptr<Tyre> tyre_;
    LapTime total_time_;
    bool is_player_;
};

#endif
