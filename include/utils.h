#pragma once

#include <limits>

#define MAX_CHARS_IGNORE std::numeric_limits <std::streamsize>::max()

inline void clearScreen();

inline void clearInput();

inline void waitForEnter(std::string prompt);
