#ifndef PITWALL_DRIVER_H
#define PITWALL_DRIVER_H

#include <string>

// Kierowca: imię i umiejętności w skali 0–100.
class Driver {
public:
    static const int MIN_SKILL = 0;
    static const int MAX_SKILL = 100;

    Driver();
    Driver(const std::string& name, int skill);

    std::string getName() const;
    int getSkill() const;
    void setSkill(int skill);
    double paceOffset() const;

private:
    std::string name_;
    int skill_;
};

#endif
