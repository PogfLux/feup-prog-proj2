#include <iostream>
#include <string>

#include "../include/utils.h"
#include "../include/leaderboard.h"
#include "../include/files.h"

int Leaderboard::pickLeaderboard() {

    unsigned int mazeNumber;

    while (true){
        std::cout << "Which maze's leaderboard do you want to see? (maze numbers range from 1 to 99, 0 to go back to the previous menu)\n\n-> ";
        if (!(std::cin >> mazeNumber) || std::cin.peek() != '\n') {

            clearScreen();
            clearInput();

            std::cout << "Please input a number.\n" << std::endl;
            continue;
        }

        clearInput();

        if (mazeNumber == 0){
            break; // go back
        } else if (mazeNumber > 99) { // we only need to check if the input is greater because we declared the var as 'unsigned'
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

    return 0; // returning 0 (not a valid maze number) signals that we wish to go back to the menu
};

void Leaderboard::showLeaderboard(const int& mazeNumber) {
    
    clearScreen();

    std::vector<std::string> rules = FileManager::readFileLines(LEADERBOARD_FILE_NAME(mazeNumber), LEADERBOARDS_PATH);

    std::cout << "Maze: " << mazeNumber << '\n' << std::endl;

    for (auto line : rules) {
        std::cout << line << "\n";
    }

    std::cout << std::endl;

};