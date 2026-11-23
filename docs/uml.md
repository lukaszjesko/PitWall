# Diagram klas PitWall

Diagram UML w składni Mermaid (GitHub rysuje go sam). Obrazek: [uml.png](uml.png).

Oznaczenia: `+` public, `-` private, kursywa = metoda czysto wirtualna,
podkreślenie = metoda statyczna, pełny romb = kompozycja (właściciel),
pusty grot = dziedziczenie,
przerywana strzałka = zależność. Operator `<<` dla `LapTime` jest
zwykłą funkcją poza klasą.

```mermaid
classDiagram
    class Game {
        -vector~Car~ cars_
        +Game()
        +run() void
        -readLine(string prompt)$ string
        -readInt(string prompt, int min, int max)$ int
        -readCompound(string prompt)$ Compound
        -isAhead(Car first, Car second)$ bool
        -listCars() void
        -addCar() void
        -removeCar() void
        -editCar() void
        -findCar(string team_name) wskaźnik na Car
        -startRace() void
        -printTable(Track track, int lap) void
    }

    class Car {
        -string team_name_
        -Driver driver_
        -unique_ptr~Tyre~ tyre_
        -LapTime total_time_
        -bool is_player_
        +Car(string team_name, Driver driver, bool is_player)
        +startRace(Compound compound) void
        +driveLap(Track track) void
        +pitStop(Compound compound, LapTime time_lost) void
        +setDriverSkill(int skill) void
        +getTeamName() string
        +getDriver() Driver
        +getTyre() Tyre
        +getTotalTime() LapTime
        +isPlayer() bool
    }

    class Driver {
        -string name_
        -int skill_
        +int MIN_SKILL$
        +int MAX_SKILL$
        +Driver()
        +Driver(string name, int skill)
        +getName() string
        +getSkill() int
        +setSkill(int skill) void
        +paceOffset() double
    }

    class LapTime {
        -int ms_
        +LapTime()
        +LapTime(int milliseconds)
        +fromSeconds(double seconds)$ LapTime
        +getMs() int
        +getSeconds() double
        +toString() string
        +toGapString() string
        +operator+(LapTime other) LapTime
        +operator-(LapTime other) LapTime
        +operator+=(LapTime other) LapTime
        +operator<(LapTime other) bool
    }

    class Track {
        -string name_
        -int laps_
        -LapTime base_lap_
        -LapTime pit_loss_
        -double wear_factor_
        +Track()
        +Track(string name, int laps, LapTime base_lap, LapTime pit_loss, double wear_factor)
        +loadFromFile(string path)$ Track
        +getName() string
        +getLaps() int
        +getBaseLap() LapTime
        +getPitLoss() LapTime
        +getWearFactor() double
    }

    class Tyre {
        <<abstract>>
        -string name_
        -char symbol_
        -double wear_
        -int age_
        +Tyre(string name, char symbol)
        +paceOffset()* double
        +wearRate()* double
        +addLap(double wear_multiplier) void
        +wearPenalty() double
        +getName() string
        +getSymbol() char
        +getWear() double
        +getAge() int
    }

    class SoftTyre {
        +SoftTyre()
        +paceOffset() double
        +wearRate() double
    }

    class MediumTyre {
        +MediumTyre()
        +paceOffset() double
        +wearRate() double
    }

    class HardTyre {
        +HardTyre()
        +paceOffset() double
        +wearRate() double
    }

    class Compound {
        <<enumeration>>
        SOFT
        MEDIUM
        HARD
    }

    Game "1" *-- "0..*" Car : ma
    Game ..> Track : wczytuje
    Car "1" *-- "1" Driver : ma
    Car "1" *-- "1" Tyre : ma
    Car "1" *-- "1" LapTime : ma
    Car ..> Track : czyta
    Track "1" *-- "2" LapTime : ma
    Tyre <|-- SoftTyre
    Tyre <|-- MediumTyre
    Tyre <|-- HardTyre
    Tyre ..> Compound
```
