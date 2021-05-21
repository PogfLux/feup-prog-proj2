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


#include "../include/game.h"

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

Maze::Maze(std::vector<Post> fences) : _fences(fences) { };

///////////////////////////////////////////////////////////////////

Game::Game(Player player, Maze maze, std::vector<Robot> robots): _player(player), _maze(maze), _robots(robots) {};

///////////////////////////////////////////////////////////////////

Player Game::getPlayer() const {

    return this-> _player;

};

///////////////////////////////////////////////////////////////////

Maze Game::getMaze() const {

    return this-> _maze;

};

///////////////////////////////////////////////////////////////////

std::vector<Robot> Game::getRobots() const {
    
    return this-> _robots;

};