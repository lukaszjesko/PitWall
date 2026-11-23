#include "game.h"

#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "console.h"

// Na start: twój zespół i pięciu rywali komputera.
Game::Game() {
    cars_.emplace_back("Warta Racing", Driver("J. Nowak", 85), true);
    cars_.emplace_back("Vistula GP", Driver("M. Kowalski", 90), false);
    cars_.emplace_back("Berlin Motor", Driver("H. Schmidt", 86), false);
    cars_.emplace_back("Scuderia Po", Driver("L. Rossi", 84), false);
    cars_.emplace_back("Seine Racing", Driver("A. Dubois", 82), false);
    cars_.emplace_back("Thames Speed", Driver("O. Clarke", 80), false);
}

// Menu padoku w pętli, aż gracz wybierze 0.
void Game::run() {
    while (true) {
        std::cout << "\n PADOK: 1 lista, 2 dodaj, 3 usuń, 4 zmień kierowcę,"
                  << " 5 wyścig, 0 koniec\n";
        int choice = readInt(" Wybór > ", 0, 5);
        if (choice == 1) {
            listCars();
        } else if (choice == 2) {
            addCar();
        } else if (choice == 3) {
            removeCar();
        } else if (choice == 4) {
            editCar();
        } else if (choice == 5) {
            startRace();
        } else {
            return;
        }
    }
}

// Czyta całą linię. Koniec wejścia (Ctrl+Z) kończy program.
std::string Game::readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    if (!std::getline(std::cin, line)) {
        std::exit(0);
    }
    return line;
}

// Pyta, aż dostanie liczbę z zakresu. std::stoi rzuca wyjątek,
// gdy tekst nie jest liczbą: łapiemy go i pytamy jeszcze raz.
int Game::readInt(const std::string& prompt, int min, int max) {
    while (true) {
        std::string line = readLine(prompt);
        try {
            int value = std::stoi(line);
            if (value >= min && value <= max) {
                return value;
            }
        } catch (const std::exception&) {
        }
        std::cout << " Podaj liczbę od " << min << " do " << max << ".\n";
    }
}

// Litera s, m albo h zamieniona na mieszankę opon.
Compound Game::readCompound(const std::string& prompt) {
    while (true) {
        std::string text = readLine(prompt);
        if (text == "s") {
            return Compound::SOFT;
        }
        if (text == "m") {
            return Compound::MEDIUM;
        }
        if (text == "h") {
            return Compound::HARD;
        }
        std::cout << " Wpisz s, m albo h.\n";
    }
}

// Kto ma mniejszy łączny czas, jest wyżej. Używa operatora < z LapTime.
bool Game::isAhead(const Car& first, const Car& second) {
    return first.getTotalTime() < second.getTotalTime();
}

void Game::listCars() const {
    for (const Car& car : cars_) {
        std::cout << " " << std::left << std::setw(16) << car.getTeamName()
                  << std::setw(16) << car.getDriver().getName()
                  << car.getDriver().getSkill() << "\n";
    }
}

// Dodawanie: nowy zespół komputera na koniec listy.
void Game::addCar() {
    std::string team = readLine(" Nazwa zespołu > ");
    if (team.empty() || findCar(team) != nullptr) {
        std::cout << " Nazwa jest pusta albo taki zespół już jest.\n";
        return;
    }
    std::string driver = readLine(" Kierowca > ");
    int skill = readInt(" Umiejętności (0-100) > ", 0, 100);
    cars_.emplace_back(team, Driver(driver, skill), false);
    std::cout << " Dodano.\n";
}

// Usuwanie: erase potrzebuje pozycji, dlatego pętla po indeksach.
// Swojego zespołu usunąć nie można.
void Game::removeCar() {
    std::string team = readLine(" Nazwa zespołu > ");
    for (int i = 0; i < static_cast<int>(cars_.size()); ++i) {
        if (cars_[i].getTeamName() == team && !cars_[i].isPlayer()) {
            cars_.erase(cars_.begin() + i);
            std::cout << " Usunięto.\n";
            return;
        }
    }
    std::cout << " Nie ma takiego zespołu komputera.\n";
}

// Wyszukiwanie i modyfikacja: findCar, potem setter.
void Game::editCar() {
    Car* car = findCar(readLine(" Nazwa zespołu > "));
    if (car == nullptr) {
        std::cout << " Nie ma takiego zespołu.\n";
        return;
    }
    car->setDriverSkill(readInt(" Nowe umiejętności (0-100) > ", 0, 100));
    std::cout << " Zapisano.\n";
}

// Zwraca wskaźnik do znalezionego samochodu albo nullptr.
Car* Game::findCar(const std::string& team_name) {
    for (Car& car : cars_) {
        if (car.getTeamName() == team_name) {
            return &car;
        }
    }
    return nullptr;
}

// Wyścig. Tor z pliku: zły plik rzuca wyjątek, łapiemy go tutaj.
// Gracz planuje opony i okrążenie zjazdu przed startem.
// Komputer zjeżdża, gdy zużycie opon przekroczy 55%.
void Game::startRace() {
    std::string path =
        readLine(" Plik toru (Enter = data/tracks/poznan.txt) > ");
    if (path.empty()) {
        path = "data/tracks/poznan.txt";
    }
    Track track;
    try {
        track = Track::loadFromFile(path);
    } catch (const std::runtime_error& error) {
        std::cout << " Błąd toru: " << error.what() << "\n";
        return;
    }
    Compound start = readCompound(" Opony na start (s/m/h) > ");
    int pit_lap = readInt(" Okrążenie zjazdu (0 = bez zjazdu) > ", 0,
                          track.getLaps() - 1);
    Compound after = readCompound(" Opony po zjeździe (s/m/h) > ");
    for (Car& car : cars_) {
        if (car.isPlayer()) {
            car.startRace(start);
        } else {
            car.startRace(Compound::MEDIUM);
        }
    }
    for (int lap = 1; lap <= track.getLaps(); ++lap) {
        for (Car& car : cars_) {
            car.driveLap(track);
            bool pit = car.getTyre().getWear() > 55.0
                       && track.getLaps() - lap > 3;
            Compound next = Compound::MEDIUM;
            if (car.isPlayer()) {
                pit = lap == pit_lap;
                next = after;
            }
            if (pit) {
                double stop = 2.0 + (std::rand() % 11) / 10.0;
                LapTime lost = track.getPitLoss() + LapTime::fromSeconds(stop);
                car.pitStop(next, lost);
            }
        }
        std::sort(cars_.begin(), cars_.end(), isAhead);
        console::clearScreen();
        printTable(track, lap);
        console::pause(200);
    }
    std::cout << "\n META! Wygrywa " << cars_[0].getDriver().getName()
              << ", czas " << cars_[0].getTotalTime() << "\n";
}

// Tabela. setw(16) = następny napis zajmie 16 znaków,
// left/right = dosunięty do lewej albo do prawej.
void Game::printTable(const Track& track, int lap) const {
    std::cout << " " << track.getName() << ", okrążenie " << lap << "/"
              << track.getLaps() << "\n\n";
    std::cout << "  P  KIEROWCA         ZESPÓŁ          "
              << "OPONY   ZUŻYCIE    ODSTĘP\n";
    for (int i = 0; i < static_cast<int>(cars_.size()); ++i) {
        const Car& car = cars_[i];
        std::string name = car.getDriver().getName();
        if (car.isPlayer()) {
            name += " (TY)";
        }
        std::string gap = "lider";
        if (i > 0) {
            gap = (car.getTotalTime() - cars_[0].getTotalTime()).toGapString();
        }
        std::cout << std::right << std::setw(3) << i + 1 << "  " << std::left
                  << std::setw(17) << name << std::setw(16) << car.getTeamName()
                  << std::setw(8) << car.getTyre().getName() << std::right
                  << std::setw(6) << static_cast<int>(car.getTyre().getWear())
                  << "%" << std::setw(10) << gap << "\n";
    }
}
