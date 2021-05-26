#pragma once

#include <limits>

#define MAX_CHARS_IGNORE std::numeric_limits <std::streamsize>::max()

void clearScreen();

void clearInput();

void waitForEnter(std::string prompt = "Press ENTER to continue...");
