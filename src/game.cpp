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

#include "../include/utils.h"
#include "../include/game.h"
#include "../include/files.h"

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

Maze::Maze(int numCols, int numRows) : _numCols(numCols), _numRows(numRows){ };

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

std::string Game::pickMaze() {

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
        if (!mazeNumber) return "RETURN"; // the user wishes to go back to the previous menu, return special string indicating so

        // check if number is within boundaries

        if (mazeNumber < 0 || mazeNumber > 99) {
            std::cout << "\nThe specified number is out of bounds, please input another number.\n" << std::endl;
            continue;
        }

        // build the file name

        auto mazeFileName = MAZE_FILE_NAME(mazeNumber);

        // check if file file exists

        if(!FileManager::fileExists(mazeFileName, MAZES_PATH)) { 
            std::cout << "The given maze does not exist. Please choose another maze to play.\n" << std::endl;
            continue;
        }
        
        this->_mazePicked = true;

        return mazeFileName;
    }
}

///////////////////////////////////////////////////////////////////

void Game::createMaze(std::string& mazeFileName) const{

    std::stringstream ss;

    

}

std::vector<Robot> Game::getRobots() const {
    
    return this-> _robots;

};