#include <iostream>
#include <string>

#include "../include/utils.h"
#include "../include/leaderboard.h"
#include "../include/files.h"

int Leaderboard::pickLeaderboard() {

    unsigned int mazeNumber;

    while (true){
        std::cout << "Which maze's leaderboard do you want to see? (maze numbers range from 1 to 99)\n\n-> ";
        if (!(std::cin >> mazeNumber) || std::cin.peek() != '\n') {

            clearScreen();
            clearInput();

            std::cout << "Please input a number.\n" << std::endl;
            continue;
        }

        clearInput();

        if (mazeNumber == 0 || mazeNumber > 99) {
            clearScreen();
            std::cout << "Not a valid maze number. \n\n";
            continue;
        }
        
        if(!FileManager::fileExists(LEADERBOARD_FILE_NAME(mazeNumber), LEADERBOARDS_PATH)) {
            clearScreen();
            std::cout << "The leaderboard for that maze doesn't exist.\n\n";
            continue;
        }
        
        return mazeNumber;
    }
};

void Leaderboard::showLeaderboard(const int& mazeNumber) {
    
    std::vector<std::string> rules = FileManager::readFileLines(LEADERBOARD_FILE_NAME(mazeNumber), LEADERBOARDS_PATH);

    for (auto line : rules) {
        std::cout << line << "\n";
    }

};