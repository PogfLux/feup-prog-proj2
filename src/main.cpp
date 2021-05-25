#include <iostream>
#include <string> 
#include <vector>
#include <sstream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <cmath>

#include "./utils.cpp" //linking errors when including utils.h temporarily fixed by including the .cpp file instead
#include "../include/main.h"
#include "../include/game.h"
#include "../include/leaderboard.h"
#include "../include/files.h"

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

    std::cout << std::endl;
};

int chooseMenuOption() {
    
    int response = -1; // not a menu option, should signal error
 
    do {

        std::cout << "Menu:" << '\n' << "1) Rules" << '\n' << "2) Play" << '\n' << "3) Leaderboard" << '\n' << "0) Exit" << "\n\n" << "Option: ";

        if (!(std::cin >> response) || std::cin.peek() != '\n') { // input is not a number
            clearInput();
            clearScreen();
            std::cout << "\nPlease input a number.\n" << std::endl;
            continue;
        }

    } while(response == -1);
    
    clearInput();

    // Sanitize response, i.e., if response is not one of the options, inform the player.

    switch (response) {
        case RULES:
        case LEADERBOARD:           
        case PLAY:
        case EXIT:
            return response;

        default:
            clearScreen();
            std::cout << "\nInvalid option, please input a valid option out of the list.\n" << std::endl;
    };
}

void makeExit() {

    waitForEnter();

    std::cout << "Until next time :-)" << std::endl;
}

int main() {

    atexit(makeExit); // we want to terminate gracefully, register this function

    FileManager::setCWD(RESOURCES_PATH);

    Game game;

    std::string mazeName;

    clearScreen();
    std::cout << "Robot Maze" << "\n\n";

    do {
        int menuChoice = chooseMenuOption();

        switch (menuChoice) {
            case RULES:
                showRules();
                break;
            case LEADERBOARD: {
                clearScreen();
                int mazeNumber = Leaderboard::pickLeaderboard();
                if (mazeNumber != 0) {
                    Leaderboard::showLeaderboard(mazeNumber);
                    waitForEnter("Press ENTER to return to main menu...");
                }
                clearScreen();
                break;
            }
            case PLAY:
                clearScreen();
                mazeName = game.pickMaze();
                break;
            case EXIT:
                exit(0); // call exit directly
        };

    } while (!game.mazePicked());

    // we only reach this point in the code if we actually picked a maze, so it's safe to parse the maze file

    game.createMaze(mazeName);

    while(!game.over()) {

    }

    return 0;
}

