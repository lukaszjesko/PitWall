# PitWall

Gra w terminalu napisana w C++17. Jesteś strategiem zespołu wyścigowego:
wybierasz opony na start i decydujesz, kiedy kierowca zjeżdża do boksu i na
jakie opony. Rywalizujesz z zespołami sterowanymi przez program.

Projekt zaliczeniowy z przedmiotu Języki obiektowe, Politechnika Poznańska.

## Funkcje

- wyścig liczony okrążenie po okrążeniu, tabela wyników odświeżana na żywo
- trzy mieszanki opon (Soft, Medium, Hard), które zużywają się i tracą tempo;
  po 60% zużycia czasy gwałtownie rosną
- pit stopy: strata w alei serwisowej plus losowy czas postoju
- rywale komputera zjeżdżają do boksu, gdy zużycie opon przekroczy 55%
- gracz planuje przed startem: opony, okrążenie zjazdu i opony po zjeździe
- padok: dodawanie, usuwanie i wyszukiwanie zespołów, zmiana umiejętności
  kierowców
- tory wczytywane z plików tekstowych; zły plik daje czytelny komunikat,
  a gra działa dalej

## Kompilacja

Potrzebny jest g++ z obsługą C++17 i make.

```
mingw32-make      # Windows (MinGW)
make              # Linux
```

Bez make:

```
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/*.cpp -o pitwall
```

## Uruchomienie

Z głównego folderu projektu, bo gra czyta tory z `data/tracks`:

```
.\pitwall.exe     # Windows (PowerShell)
./pitwall         # Linux
```

## Jak grać

1. Twój zespół to Warta Racing. W padoku możesz dodawać, usuwać
   i wyszukiwać zespoły oraz zmieniać umiejętności kierowców.
2. Wybierz „5 wyścig” i podaj plik toru (Enter = Tor Poznań).
3. Zaplanuj wyścig: opony na start (`s`, `m` albo `h`), okrążenie zjazdu
   (0 = bez zjazdu) i opony po zjeździe. Potem wyścig leci na żywo.

Soft jest najszybsza, ale zużywa się najszybciej. Hard odwrotnie. Wygrywa
ten, kto dobrze dobierze opony i moment zjazdu.

## Architektura

Diagram klas: [docs/uml.md](docs/uml.md).

| Klasa | Odpowiada za |
|---|---|
| `Game` | padok i wyścig: pętla okrążeń, pit stopy, tabela; ma samochody |
| `Car` | samochód: kierowca, opona, łączny czas |
| `Driver` | imię i umiejętności kierowcy |
| `LapTime` | czas w milisekundach z operatorami `+`, `+=`, `-`, `<`, `<<` |
| `Track` | parametry toru i wczytywanie ich z pliku |
| `Tyre` → `SoftTyre`, `MediumTyre`, `HardTyre` | tempo i zużycie opon |

Najważniejsze mechanizmy:

- **Dziedziczenie i polimorfizm.** `Tyre` jest klasą abstrakcyjną, a Soft,
  Medium i Hard ją dziedziczą. Samochód liczy czas okrążenia przez metody
  wirtualne opony i nie wie, jaka to mieszanka.
- **Kompozycja.** `Car` ma na własność kierowcę i oponę (`std::unique_ptr`,
  bez ręcznego `new` i `delete`), a `Game` ma wszystkie samochody.
- **Operatory.** `LapTime` sumuje czasy (`+`, `+=`), liczy odstępy (`-`),
  sortuje tabelę (`<`) i wypisuje czas jako `1:31.452` (`<<`).
- **Wyjątki.** `Track::loadFromFile` rzuca `std::runtime_error`, gdy pliku nie
  ma albo ma zły format. `Game::startRace` łapie go, pokazuje komunikat
  i wraca do padoku. `Game::readInt` łapie wyjątek z `std::stoi`, gdy wpisany
  tekst nie jest liczbą.

## Format pliku toru

W pierwszej linii nazwa toru, potem cztery pary „opis liczba” w tej
kolejności:

```
Tor Poznań
okrazenia 30
czas_okrazenia 91.5
strata_w_boksie 21.0
zuzycie 1.0
```

- `okrazenia`: liczba okrążeń
- `czas_okrazenia`: bazowy czas okrążenia w sekundach
- `strata_w_boksie`: strata czasu w alei serwisowej w sekundach
- `zuzycie`: mnożnik zużycia opon (1.0 = normalne)

Plik `data/test/zepsuty_tor.txt` ma celowy błąd i służy do pokazania obsługi
wyjątku.

## Przykład działania

```
 Tor Poznań, okrążenie 15/30

  P  KIEROWCA         ZESPÓŁ          OPONY   ZUŻYCIE    ODSTĘP
  1  L. Rossi         Scuderia Po     Medium      49%     lider
  2  H. Schmidt       Berlin Motor    Medium      49%    +0.330
  3  A. Dubois        Seine Racing    Medium      49%    +0.440
  4  M. Kowalski      Vistula GP      Medium      49%    +1.200
  5  O. Clarke        Thames Speed    Medium      49%    +1.890
  6  J. Nowak (TY)    Warta Racing    Medium      13%   +16.184
```

```
 Tor Poznań, okrążenie 30/30

  P  KIEROWCA         ZESPÓŁ          OPONY   ZUŻYCIE    ODSTĘP
  1  J. Nowak (TY)    Warta Racing    Medium      62%     lider
  2  H. Schmidt       Berlin Motor    Medium      42%    +1.372
  3  L. Rossi         Scuderia Po     Medium      42%    +1.532
  4  M. Kowalski      Vistula GP      Medium      42%    +2.632
  5  A. Dubois        Seine Racing    Medium      42%    +2.932
  6  O. Clarke        Thames Speed    Medium      42%    +3.142

 META! Wygrywa J. Nowak, czas 45:55.974
```
