#include <iostream>

#include "../include/utils.h"

inline void clearScreen() {std::cout << std::string(500, '\n') << std::endl;};

inline void clearInput() {std::cin.clear(); std::cin.ignore(MAX_CHARS_IGNORE, '\n');};

inline void waitForEnter() {
    std::cout << "Press ENTER to continue..." << std::endl;
    if (std::cin.peek() == '\n') std::cin.ignore(MAX_CHARS_IGNORE, '\n');
}
