#include <iostream>
#include <string> 
#include <vector>
#include <sstream>
#include <fstream>
#include <chrono>
#include <limits>
#include <algorithm>
#include <cmath>

#include "../include/utils.h"
#include "../include/main.h"
#include "../include/game.h"
#include "../include/leaderboard.h"
#include "../include/files.h"

inline void clearScreen() {std::cout << std::string(500, '\n') << std::endl;};

inline void clearInput() {std::cin.clear(); std::cin.ignore(MAX_CHARS_IGNORE, '\n');};

inline void waitForEnter() {
    std::cout << "Press ENTER to continue..." << std::endl;
    if (std::cin.peek() == '\n') std::cin.ignore(MAX_CHARS_IGNORE, '\n');
}

enum GameMenuOption {
    EXIT, RULES, PLAY, LEADERBOARD
};

void showRules() { 
    
    clearScreen();

    if (FileManager::fileExists("RULES.TXT")) {

        std::vector<std::string> rules = FileManager::readFileLines("RULES.TXT");

        for (auto line : rules)
            std::cout << line << "\n";
    };
};

bool showMenu() {
    
    int response;

    std::cout << "Robot Maze" << "\n\n" << "Menu:";
    
    while (true) {

        std::cout << '\n' << "1) Rules" << '\n' << "2) Play" << '\n' << "3) Leaderboard" << '\n' << "0) Exit" << "\n\n" << "Option: ";

        if (!(std::cin >> response) || std::cin.peek() != '\n') { // input is not a number
            clearInput();
            clearScreen();
            std::cout << "\nPlease input a number.\n" << std::endl;
            continue;
        }

        clearInput();

        // Sanitize response, i.e., if response is not one of the options, inform the player.

        switch (response) {
            case RULES:
                clearScreen();
                showRules();
                break;
                
            case LEADERBOARD: {
                clearScreen();
                int mazeNumber = Leaderboard::pickLeaderboard();
                Leaderboard::showLeaderboard(mazeNumber);
                break;
            }
            case PLAY:
                return true;

            case EXIT:
                return false;
            
            default:
                clearScreen();
                std::cout << "\nInvalid option, please input a valid option out of the list.\n" << std::endl;
        };
    }
}

void makeExit() {

    waitForEnter();

    std::cout << "Until next time :-)" << std::endl;

}

int main() {

    atexit(makeExit);

    FileManager::setCWD(RESOURCES_PATH);

    Game game;

    clearScreen();

    showMenu();

}

