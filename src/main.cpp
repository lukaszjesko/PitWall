#include <cstdlib>
#include <ctime>

#include "console.h"
#include "game.h"

int main() {
    std::srand(std::time(nullptr));
    console::setup();
    Game game;
    game.run();
    return 0;
}
