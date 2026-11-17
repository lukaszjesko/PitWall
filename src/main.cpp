#include <iostream>

#include "console.h"
#include "driver.h"
#include "lap_time.h"

void printDriver(const Driver& driver) {
    std::cout << "  " << console::padRight(driver.getName(), 14)
              << "umiejętności " << driver.getSkill() << ", na okrążeniu "
              << driver.paceOffset() << " s\n";
}

int main() {
    console::setup();
    std::cout << console::colored("PITWALL", console::BOLD)
              << " — test klas Driver i LapTime\n\n";

    Driver kowalski("M. Kowalski", 90);
    Driver nowak("J. Nowak", 150);
    Driver reserve;
    std::cout << "Kierowcy:\n";
    printDriver(kowalski);
    printDriver(nowak);
    printDriver(reserve);

    LapTime first = LapTime::fromSeconds(91.452);
    LapTime second = LapTime::fromSeconds(90.875);
    std::cout << "\nCzasy:\n";
    std::cout << "  okrążenie 1: " << first << "\n";
    std::cout << "  okrążenie 2: " << second << "\n";
    std::cout << "  razem:       " << first + second << "\n";
    std::cout << "  różnica:     " << (first - second).toGapString() << "\n";
    if (second < first) {
        std::cout << "  Drugie okrążenie było szybsze.\n";
    }
    return 0;
}
