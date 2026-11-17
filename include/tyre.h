#ifndef PITWALL_TYRE_H
#define PITWALL_TYRE_H

#include <memory>
#include <string>

enum class Compound { SOFT, MEDIUM, HARD };

// Klasa bazowa opony. Abstrakcyjna: nie da się zrobić "po prostu opony",
// tylko konkretną mieszankę (klasy pochodne niżej).
class Tyre {
public:
    Tyre(const std::string& name, char symbol);
    virtual ~Tyre();

    virtual double paceOffset() const = 0;
    virtual double wearRate() const = 0;

    void addLap(double wear_multiplier);
    double wearPenalty() const;

    std::string getName() const;
    char getSymbol() const;
    double getWear() const;
    int getAge() const;

private:
    std::string name_;
    char symbol_;
    double wear_;
    int age_;
};

class SoftTyre : public Tyre {
public:
    SoftTyre();
    double paceOffset() const override;
    double wearRate() const override;
};

class MediumTyre : public Tyre {
public:
    MediumTyre();
    double paceOffset() const override;
    double wearRate() const override;
};

class HardTyre : public Tyre {
public:
    HardTyre();
    double paceOffset() const override;
    double wearRate() const override;
};

// Fabryka: robi oponę wybranej mieszanki.
std::unique_ptr<Tyre> makeTyre(Compound compound);

#endif
