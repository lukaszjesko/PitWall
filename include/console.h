#ifndef PITWALL_CONSOLE_H
#define PITWALL_CONSOLE_H

#include <string>

// Wszystko, co dotyczy wyglądu w terminalu: polskie znaki, kolory
// i czyszczenie ekranu.
namespace console {

// Kody ANSI: terminal nie wypisuje ich, tylko zmienia kolor tekstu.
const std::string RESET = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string CYAN = "\033[36m";

void setup();
void clearScreen();
void pause(int milliseconds);
std::string colored(const std::string& text, const std::string& color);

}  // namespace console

#endif
