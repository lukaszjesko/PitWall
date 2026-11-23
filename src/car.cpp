#include "car.h"

#include <cstdlib>

Car::Car(const std::string& team_name, const Driver& driver, bool is_player)
    : team_name_(team_name),
      driver_(driver),
      tyre_(makeTyre(Compound::MEDIUM)),
      is_player_(is_player) {}

// Przed startem: nowe opony i czas od zera.
void Car::startRace(Compound compound) {
    tyre_ = makeTyre(compound);
    total_time_ = LapTime();
}

// Jedno okrążenie: czas = baza toru + opona + zużycie + kierowca
// + losowo od -0,25 do +0,25 s. Samochód nie wie, jaka to mieszanka:
// decydują metody wirtualne opony (polimorfizm).
void Car::driveLap(const Track& track) {
    double noise = (std::rand() % 51 - 25) / 100.0;
    double seconds = track.getBaseLap().getSeconds() + tyre_->paceOffset()
                     + tyre_->wearPenalty() + driver_.paceOffset() + noise;
    total_time_ += LapTime::fromSeconds(seconds);
    tyre_->addLap(track.getWearFactor());
}

// Pit stop: doliczamy stratę i zakładamy nowe opony.
// Starą oponę unique_ptr usuwa sam.
void Car::pitStop(Compound compound, const LapTime& time_lost) {
    total_time_ += time_lost;
    tyre_ = makeTyre(compound);
}

void Car::setDriverSkill(int skill) {
    driver_.setSkill(skill);
}

std::string Car::getTeamName() const {
    return team_name_;
}

const Driver& Car::getDriver() const {
    return driver_;
}

const Tyre& Car::getTyre() const {
    return *tyre_;
}

LapTime Car::getTotalTime() const {
    return total_time_;
}

bool Car::isPlayer() const {
    return is_player_;
}
