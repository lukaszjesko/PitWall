#include "console.h"

#include <chrono>
#include <iostream>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#endif

namespace console {

// Tylko na Windows: polskie znaki (UTF-8) i włączenie kolorów w konsoli.
void setup() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (GetConsoleMode(output, &mode)) {
        SetConsoleMode(output, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
#endif
}

void clearScreen() {
    std::cout << "\033[2J\033[H";
}

void pause(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

std::string colored(const std::string& text, const std::string& color) {
    return color + text + RESET;
}

}  // namespace console
