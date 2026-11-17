#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

#include "console.h"
#include "tyre.h"

// Funkcja dostaje referencję do klasy bazowej Tyre i nie wie, jaka to
// mieszanka. Mimo to każda zużywa się po swojemu: to jest polimorfizm.
void testTyre(Tyre& tyre) {
    const int LAPS = 25;
    std::cout << console::colored(tyre.getName(), console::BOLD) << "\n";
    for (int lap = 1; lap <= LAPS; ++lap) {
        tyre.addLap(1.0);
        if (lap % 5 == 0) {
            std::cout << "  po " << std::setw(2) << lap << " okr.: zużycie "
                      << std::setw(5) << tyre.getWear() << "%, strata "
                      << tyre.paceOffset() + tyre.wearPenalty() << " s\n";
        }
    }
}

int main() {
    console::setup();
    std::cout << console::colored("PITWALL", console::BOLD)
              << " — test opon (strata względem bazowego okrążenia)\n\n"
              << std::fixed << std::setprecision(2);

    std::vector<std::unique_ptr<Tyre>> tyres;
    tyres.push_back(makeTyre(Compound::SOFT));
    tyres.push_back(makeTyre(Compound::MEDIUM));
    tyres.push_back(makeTyre(Compound::HARD));
    for (const std::unique_ptr<Tyre>& tyre : tyres) {
        testTyre(*tyre);
    }
    return 0;
}
