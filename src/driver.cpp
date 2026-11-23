#include "driver.h"

Driver::Driver() : name_("Rezerwowy"), skill_(50) {}

Driver::Driver(const std::string& name, int skill)
    : name_(name), skill_(MIN_SKILL) {
    setSkill(skill);
}

std::string Driver::getName() const {
    return name_;
}

int Driver::getSkill() const {
    return skill_;
}

// Setter pilnuje zakresu: 150 zamieni na 100, -5 na 0
void Driver::setSkill(int skill) {
    if (skill < MIN_SKILL) {
        skill = MIN_SKILL;
    } else if (skill > MAX_SKILL) {
        skill = MAX_SKILL;
    }
    skill_ = skill;
}

// Ile sekund na okrążeniu kierowca zyskuje (minus) albo traci (plus).
double Driver::paceOffset() const {
    const int AVERAGE_SKILL = 50;
    const double SECONDS_PER_POINT = 0.01;
    return (AVERAGE_SKILL - skill_) * SECONDS_PER_POINT;
}
