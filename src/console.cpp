// Blok Windows musi stać przed nagłówkami biblioteki standardowej:
// MinGW sam definiuje NOMINMAX w <iostream>.
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

#include "console.h"

#include <chrono>
#include <iostream>
#include <thread>

namespace console {

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

int displayWidth(const std::string& text) {
    int width = 0;
    for (char byte : text) {
        // W UTF-8 polska litera to 2 bajty. Drugi ma postać 10xxxxxx
        // i nie zajmuje miejsca na ekranie, więc go nie liczymy.
        if ((static_cast<unsigned char>(byte) & 0xC0) != 0x80) {
            ++width;
        }
    }
    return width;
}

std::string padRight(const std::string& text, int width) {
    int missing = width - displayWidth(text);
    if (missing <= 0) {
        return text;
    }
    return text + std::string(missing, ' ');
}

std::string padLeft(const std::string& text, int width) {
    int missing = width - displayWidth(text);
    if (missing <= 0) {
        return text;
    }
    return std::string(missing, ' ') + text;
}

}  // namespace console
