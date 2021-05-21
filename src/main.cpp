#include <iostream>
#include <string>
#include <limits>

#include "../include/main.h"

#define MAX_CHARS_IGNORE std::numeric_limits <std::streamsize>::max()

inline void clearScreen() {std::cout << std::string(500, '\n') << std::endl;}

inline void clearInput() {std::cin.clear(); std::cin.ignore(MAX_CHARS_IGNORE);}

int main() {

    std::cout << "I work" << std::endl;

    return 0;
}