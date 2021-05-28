#pragma once

#include <limits>

#define MAX_CHARS_IGNORE std::numeric_limits <std::streamsize>::max()

/**
 * @brief Clears the screen
 * 
 */
void clearScreen();

/**
 * @brief Clears the standar input stream
 * 
 */
void clearInput();

/**
 * @brief Waits for the user to press ENTER
 * 
 * @param prompt the prompt to show, defaults to "Press ENTER to continue..." 
 */
void waitForEnter(std::string prompt = "Press ENTER to continue...");
