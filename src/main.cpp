#include <iostream>
#include <string> 
#include <vector>
#include <sstream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <cmath>

#include "../include/utils.h"
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
            response = -1;
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
            return -1; // erroneous response
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

    int mazeNumber;

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
                mazeNumber = game.pickMaze();
                break;

            case EXIT:
                exit(0); // call exit directly

            default:
                clearScreen();
                std::cout << "\nInvalid option, please input a valid option out of the list.\n" << std::endl;      
        };

    } while (!game.mazePicked());

    // we only reach this point in the code if we actually picked a maze, so it's safe to parse the maze file

    game.createMaze(mazeNumber);

    clearScreen();

    auto start = std::chrono::high_resolution_clock::now();

    while (!game.over()) {

        game.getEntityPositionsInBoard();
        game.printBoard();

        char playerMove = game.pollPlayerMovement();

        Position newPlayerPos = game.getNewPlayerPosition(playerMove);

        if (!game.isValidPlayerPosition(newPlayerPos)) {

            clearScreen();
            std::cout << "Invalid move, input another move.\n";

        } else {
            game.movePlayer(newPlayerPos);
            if(!game.over()) // the player could have killed himself, in which case the game should be over right away
                game.moveRobots();
                clearScreen();
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    int time = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    game.getEntityPositionsInBoard(); // we need to call this to update the internal representation of the board
    game.printBoard();

    if (game.getPlayer().isAlive()) { // game won 
    
        auto playerName = Leaderboard::getPlayerName();
    
        Node n = {playerName, time};

        Leaderboard::readLeaderboardFromFile(LEADERBOARD_FILE_NAME(game.getMaze().getMazeNumber()));
        Leaderboard::addEntryToLeaderboard(n);
        Leaderboard::sortLeaderboard();
        Leaderboard::writeLeaderboardToFile(LEADERBOARD_FILE_NAME(game.getMaze().getMazeNumber()));
    
    } else { //dumbass lost the easiest game in the world, he must be as retarded as Peras
        std::cout << '\n';
        std::cout << "Oh no, looks like you have lost, try again next time." << std::endl;
    }

    return 0;
}

