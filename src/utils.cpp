#include <iostream>
#include <string>

#include "../include/utils.h"

void clearScreen() {std::cout << std::string(500, '\n') << std::endl;};

void clearInput() {std::cin.clear(); std::cin.ignore(MAX_CHARS_IGNORE, '\n');};

void waitForEnter(std::string prompt) {
    if (std::cin.good()) std::cout << prompt << std::endl;
    if (std::cin.peek() == '\n') std::cin.ignore(MAX_CHARS_IGNORE, '\n');
}
