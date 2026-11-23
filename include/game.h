#ifndef PITWALL_GAME_H
#define PITWALL_GAME_H

#include <string>
#include <vector>

#include "car.h"
#include "track.h"

// Cała gra: padok (lista, dodaj, usuń, znajdź i zmień) i wyścig.
// Game jest właścicielem samochodów (kompozycja).
class Game {
public:
    Game();

    void run();

private:
    static std::string readLine(const std::string& prompt);
    static int readInt(const std::string& prompt, int min, int max);
    static Compound readCompound(const std::string& prompt);
    static bool isAhead(const Car& first, const Car& second);

    void listCars() const;
    void addCar();
    void removeCar();
    void editCar();
    Car* findCar(const std::string& team_name);
    void startRace();
    void printTable(const Track& track, int lap) const;

    std::vector<Car> cars_;
};

#endif
