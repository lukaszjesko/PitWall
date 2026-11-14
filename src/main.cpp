#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif
#include <iostream>

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    std::cout << "PitWall" << std::endl;
    std::cout << "Zażółć gęślą jaźń" << std::endl;
    return 0;
}
