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

void Maze::addExit(Exit e) { this->_exits.push_back(e); };

int Maze::getNumCols() const{ return this->_numCols; };

int Maze::getNumRows() const{ return this->_numRows; };

std::vector<Exit> Maze::getExits() const{ return this->_exits; };

std::vector<Post> Maze::getPosts() const{ return this->_posts; };

bool Maze::collidesWithNonElectricPost(Position pos) const { 

    for (Post p : this->_posts) {
        if (p.isElectric()) continue;

        if (p.getPosition() == pos) 
            return true;
    }

    return false;
};

///////////////////////////////////////////////////////////////////

Game::Game() : _gameOver(false), _mazePicked(false) { };

///////////////////////////////////////////////////////////////////

Player& Game::getPlayer() {

    return _player;

};

///////////////////////////////////////////////////////////////////

Maze Game::getMaze() const {

    return this-> _maze;

};

bool Game::over() const {

    return this->_gameOver;

};

bool Game::mazePicked() const {

    return this->_mazePicked;

};

void Game::setMaze(Maze maze) {

    this->_maze = maze;

}

int Game::getAliveRobotsNum() {

    return this->_aliveRobots;

}

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

    std::cout << numRows << " " << numCols << std::endl;

    Maze maze = Maze(numCols, numRows, mazeNumber);
    
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
                    maze.addPost(post);

                    break;
                }
                
                case 'r':
                case 'R': { // we found a robot
                    
                    Position pos = {j, i};
                    bool isAlive = (c == 'R');

                    Robot robot = Robot(pos, isAlive);
                    this->_robots.push_back(robot);

                    this->_aliveRobots += isAlive; // since this var is a bol, it evaluates to either 1 or 0

                    break;
                }

                case 'H': { // we found the player

                    Position pos = {j, i};

                    this->_player = Player(pos, true); // the player always starts out alive.
                    break;
                }

                case 'O': { // we found an exit

                    Exit exit = {j, i};

                    maze.addExit(exit);
                    break;
                }
            }
        }
    }

    this->setMaze(maze);

}

std::vector<Robot>& Game::getRobots() {
    
    return _robots;

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
            this->printBoard();
            std::cout << "Invalid input.\n" << std::endl;
            movement = ERROR;
        }
        
    } while (!(movement >= 'a' && movement <= 'z'));
    
    return movement;  
};

void Game::getEntityPositionsInBoard() {

    std::vector<char> boardChars;

    auto player = this->getPlayer();
    auto robots = this->getRobots();
    auto maze = this->getMaze();
    auto exits = maze.getExits();
    auto posts = maze.getPosts();

    int width = this->getMaze().getNumCols(), height = this->getMaze().getNumRows();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {

            Position pos = {j, i};

            if(player.getPosition() == pos)
                boardChars.push_back(player.isAlive() ? 'H' : 'h');
            else {

                bool continueLoop = false;

                for (const auto& robot : robots)
                    if (robot.getPosition() == pos) {
                        boardChars.push_back(robot.isAlive() ? 'R' : 'r');
                        continueLoop = true;
                        break; // we need to 'break' here to not have duplicates
                    }

                if (continueLoop) continue;

                for (const auto& exit : exits)
                    if (exit == pos) {
                        boardChars.push_back('O');
                        continueLoop = true;
                    }

                if (continueLoop) continue;

                for (const auto& post : posts){
                    if (post.getPosition() == pos){
                        boardChars.push_back(post.isElectric() ? '*' : '+');
                        continueLoop = true;
                    }
                }

                if (continueLoop) continue;

                boardChars.push_back(' ');
            }
        }        
    }

    this->_boardChars = boardChars;
};

void Game::printBoard() { 
  
  for (int i = 0; i < this->_boardChars.size(); i++) {

        if (i % this->getMaze().getNumCols() == 0) // we reached the end of a row
            std::cout << '\n';

        std::cout << this->_boardChars.at(i);
    }

    std::cout << '\n' << std::endl;

};

Position Game::getNewPlayerPosition(char playerMove) {

    Position currPos = this->getPlayer().getPosition();

    switch (playerMove) {

        case 'q':
            return {currPos.x - 1, currPos.y - 1};
        
        case 'w':
            return {currPos.x, currPos.y - 1};
        
        case 'e':
            return {currPos.x + 1, currPos.y - 1};
        
        case 'd':
            return {currPos.x + 1, currPos.y};
        
        case 'c':
            return {currPos.x + 1, currPos.y + 1};
        
        case 'x':
            return {currPos.x, currPos.y + 1};
        
        case 'z':
            return {currPos.x - 1, currPos.y + 1};
        
        case 'a':
            return {currPos.x - 1, currPos.y};
        
        case 's' : 
        default:
            return currPos;
    }   
}

bool Game::isValidPlayerPosition(const Position& newPos) {

    for (const Robot& robot : this->getRobots()) {
        if (robot.isAlive()) continue; 

        Position robotPos = robot.getPosition();
        
        if (robotPos == newPos) {
            return false;
        }
    }  

    if (this->getMaze().collidesWithNonElectricPost(newPos))
        return false;
    
    return true;

    /* switch (this->_boardChars.at(newPos.x + (this->getMaze().getNumCols() * newPos.y))) {
        case '+':
        case 'r': 
            return false;

        default:
            return true;
    } */

}

Position Game::getRobotMove(const Robot& robot) {
    

    auto currPos = robot.getPosition();
    auto playerPos = this->getPlayer().getPosition();

    int dx, dy; // the change of movement in the robots

    dx = (currPos.x < playerPos.x) ? 1 : (currPos.x > playerPos.x) ? -1 : 0;
    dy = (currPos.y < playerPos.y) ? 1 : (currPos.y > playerPos.y) ? -1 : 0;

    return {currPos.x + dx, currPos.y + dy};
}

void Game::moveRobots() {
    
    for (auto &robot : this->getRobots()) {
        if(!robot.isAlive()) continue; // we do not want to move dead robots
        
        bool breakLoop = false, continueLoop = false;

        Position prevPos = robot.getPosition();

        Position nextPos = getRobotMove(robot);

        if (nextPos == this->getPlayer().getPosition()) {
            this->getPlayer().die();
            this->_gameOver = true;
            return; // we can return right away since we lost
        }

        for (auto &otherRobot : this->getRobots()) {
            if (otherRobot == robot) continue; // no checking ourselves twice

            if (otherRobot.getPosition() == nextPos) {

                robot.move(nextPos);
                robot.die(); // kill the robot that moved
                robot.setState(Robot::DEAD_STATE::STUCK);
                if (otherRobot.isAlive()) {
                    otherRobot.die(); // kill the other robot and stop checking for robots to kill
                    otherRobot.setState(Robot::DEAD_STATE::STUCK);
                }
                continueLoop = true;
                this->_aliveRobots -= 2;
                break;
            }
        }

        if (continueLoop) continue;

        for (auto post : this->getMaze().getPosts()){

            if (post.getPosition() == nextPos) {
                if (!post.isElectric())
                    robot.move(nextPos);
                robot.die();
                robot.setState(post.isElectric() ? Robot::DEAD_STATE::DEAD : Robot::DEAD_STATE::STUCK);
                this->_aliveRobots--;
                continueLoop = true;
                break;
            }
        }
        
        if (continueLoop) continue;

        robot.move(nextPos);

        std::cout << "hum" << std::endl;
    }    
}


void Game::movePlayer(Position newPos) {
    
    for (const auto& exit : this->getMaze().getExits()){

        if (exit == newPos){
            this->getPlayer().move(newPos);
            this->_gameOver = true;
            return;
        }
    }

    for (const auto& post : this->getMaze().getPosts()) {

        if (!post.isElectric()) continue;

        if (post.getPosition() == newPos) {
            this->getPlayer().die();
            this->_gameOver = true;
            return;
        }

    }

    if (this->_aliveRobots == 0) {
        this->_gameOver = true;
        return;
     } else {
        for (const auto& robot : this->getRobots()) {
            if (robot.getPosition() == newPos) {
                this->getPlayer().die();
                this->_gameOver = true;
                return;
            }
        }
    }

    this->getPlayer().move(newPos);
}
