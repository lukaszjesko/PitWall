#include "tyre.h"

Tyre::Tyre(const std::string& name, char symbol)
    : name_(name), symbol_(symbol), wear_(0.0), age_(0) {}

Tyre::~Tyre() = default;

// wearRate() jest wirtualna, więc każda mieszanka zużywa się po swojemu,
// choć ta metoda jest napisana tylko raz, w klasie bazowej.
void Tyre::addLap(double wear_multiplier) {
    const double MAX_WEAR = 100.0;
    wear_ += wearRate() * wear_multiplier;
    if (wear_ > MAX_WEAR) {
        wear_ = MAX_WEAR;
    }
    ++age_;
}

// Do 60% zużycia opona traci mało, potem gwałtownie ("klif").
double Tyre::wearPenalty() const {
    const double CLIFF = 60.0;
    const double PENALTY_BEFORE_CLIFF = 0.03;
    const double PENALTY_AFTER_CLIFF = 0.25;
    if (wear_ <= CLIFF) {
        return wear_ * PENALTY_BEFORE_CLIFF;
    }
    return CLIFF * PENALTY_BEFORE_CLIFF
           + (wear_ - CLIFF) * PENALTY_AFTER_CLIFF;
}

std::string Tyre::getName() const {
    return name_;
}

char Tyre::getSymbol() const {
    return symbol_;
}

double Tyre::getWear() const {
    return wear_;
}

int Tyre::getAge() const {
    return age_;
}

SoftTyre::SoftTyre() : Tyre("Soft", 'S') {}

double SoftTyre::paceOffset() const {
    return -1.4;
}

double SoftTyre::wearRate() const {
    return 5.5;
}

MediumTyre::MediumTyre() : Tyre("Medium", 'M') {}

double MediumTyre::paceOffset() const {
    return -0.7;
}

double MediumTyre::wearRate() const {
    return 3.3;
}

HardTyre::HardTyre() : Tyre("Hard", 'H') {}

double HardTyre::paceOffset() const {
    return 0.0;
}

double HardTyre::wearRate() const {
    return 2.1;
}

std::unique_ptr<Tyre> makeTyre(Compound compound) {
    switch (compound) {
    case Compound::SOFT:
        return std::make_unique<SoftTyre>();
    case Compound::MEDIUM:
        return std::make_unique<MediumTyre>();
    case Compound::HARD:
        return std::make_unique<HardTyre>();
    }
    return std::make_unique<MediumTyre>();
}
