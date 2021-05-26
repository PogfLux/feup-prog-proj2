/**
 * @file game.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <sstream>
#include <algorithm>

#include "../include/utils.h"
#include "../include/game.h"
#include "../include/files.h"
#include "../include/entities.h"

Post::Post(Position pos, bool electric) : _pos(pos), _electric(electric) { };

///////////////////////////////////////////////////////////////////

void Post::setElectric(bool newState){

    this->_electric = newState;

};

///////////////////////////////////////////////////////////////////

Position Post::getPosition() const {

    return this-> _pos;

};

///////////////////////////////////////////////////////////////////

bool Post::isElectric() const {

    return this-> _electric;

};

///////////////////////////////////////////////////////////////////

Maze::Maze() { };

Maze::Maze(int numCols, int numRows, int mazeNumber) : _numCols(numCols), _numRows(numRows), _mazeNumber(mazeNumber) { };

int Maze::getMazeNumber() const { return this->_mazeNumber; };

void Maze::addPost(Post p) { this->_posts.push_back(p); };

void Maze::addExit(Exit c) { this->_exits.push_back(c); };

///////////////////////////////////////////////////////////////////

Game::Game() : _gameOver(false), _mazePicked(false) { };

///////////////////////////////////////////////////////////////////

Player Game::getPlayer() const {

    return this-> _player;

};

///////////////////////////////////////////////////////////////////

Maze Game::getMaze() const {

    return this-> _maze;

};

bool Game::over() const {

    return this->_gameOver;;

};

bool Game::mazePicked() const {

    return this->_mazePicked;

};

int Game::pickMaze() {

    int mazeNumber;

    while (true) { // make while (true) because the user can keep giving wrong inputs, maybe change later ?
        
        std::cout << "Write the number, from 1 to 99, of the maze you want to play.\nIf you wish to return to the previous menu enter 0 instead.\n" << std::endl; // flush this string immediately
        std::cout << "Maze number: ";
        if (!(std::cin >> mazeNumber) || std::cin.peek() != '\n') { // there was an error getting maze number or the user did not input just a number

            clearInput();
            clearScreen();
            std::cout << "\nPlease input just a number.\n" << std::endl;
            continue;

        }

        clearInput();

        clearScreen();
        if (!mazeNumber) return 0; // the user wishes to go back to the previous menu, return special string indicating so

        // check if number is within boundaries

        if (mazeNumber < 0 || mazeNumber > 99) {
            std::cout << "\nThe specified number is out of bounds, please input another number.\n" << std::endl;
            continue;
        }

        // check if file file exists

        if(!FileManager::fileExists(MAZE_FILE_NAME(mazeNumber), MAZES_PATH)) { 
            std::cout << "The given maze does not exist. Please choose another maze to play.\n" << std::endl;
            continue;
        }
        
        this->_mazePicked = true;

        return mazeNumber;
    }
}

///////////////////////////////////////////////////////////////////

void Game::createMaze(int mazeNumber) { //reads the maze file to find out posts, robots and the player

    int numRows, numCols;

    std::string mazeFileName = MAZE_FILE_NAME(mazeNumber);
    std::vector<std::string> fileLines = FileManager::readFileLines(mazeFileName, MAZES_PATH);

    std::string line = fileLines.at(0);

    std::stringstream ss(line);
    char sep;

    ss >> numRows;
    ss >> sep;
    ss >> numCols;

    this->_maze = Maze(numCols, numRows, mazeNumber);
    
    for (int i = 0; i < numRows; i++){

        line = fileLines.at(i + 1);

        for (int j = 0; j < numCols; j++) {
            
            char c = line.at(j);

            switch (c) {
                case '+':
                case '*': { // we found a post
                    
                    Position pos = {j, i};
                    bool isElectric = (c == '*');

                    Post post = Post(pos, isElectric);
                    this->getMaze().addPost(post);

                    break;
                }
                
                case 'r':
                case 'R': { // we found a robot
                    
                    Position pos = {j, i};
                    bool isAlive = (c == 'R');

                    Robot robot = Robot(pos, isAlive);
                    this->_robots.push_back(robot);

                    break;
                }

                case 'H': { // we found the player

                    Position pos = {j, i};

                    this->_player = Player(pos, true); // the player always starts out alive.
                    break;
                }

                case 'O': { // we found an exit

                    Exit exit = {j, i};

                    this->getMaze().addExit(exit);
                    break;
                }
            }
        }
    }

}

std::vector<Robot> Game::getRobots() const {
    
    return this-> _robots;

};

const std::vector<char> Game::validMoves = {'q', 'w', 'e', 'd', 'c', 'x', 'z', 'a', 's'};

char Game::pollPlayerMovement() {
    
    const char ERROR = 0;

    char movement = ERROR;
    
    label: do {
        std::cout << "What movement do you want to make?\n-> ";
        std::cin >> movement;

        if (std::cin.eof()) { // the user wants to quit the game gracefully

            std::cout << std::endl;

            exit(0);
        }

        // EOF was not signalled, validate input normally

        if(std::cin.bad() || std::cin.peek() != '\n') { 
            
            clearInput();
            clearScreen();

            std::cout << "An error occurred, please repeat the previous action.\n" << std::endl;
            
            movement = ERROR;
            continue;         
        }
        
        clearInput();

        movement = tolower(movement);

        if (std::find(Game::validMoves.begin(), Game::validMoves.end(), movement) == Game::validMoves.end()) { // the move that the user entered is not one of the valid moves
            clearScreen();
            std::cout << "Invalid input.\n" << std::endl;

            movement = ERROR;
        }
        
    } while (!(movement >= 'a' && movement <= 'z'));
    
    return movement;  
};
