/**
 * @file entities.cpp
 * @author Nuno Pereira (up202007865@fe.up.pt)
 * @author José Osório (up202004653@fe.up.pt)
 * @brief The specific implementations of the entity classes.
 * @version 1.0
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../include/entities.h"

Robot::Robot() { };

Robot::Robot(Position pos, bool alive) : _pos(pos), _alive(alive) { 
    this->_id = Robot::setRobotID();
};

inline int Robot::setRobotID() {
    static int id = 1;

    return id++;
};

void Robot::setState(DEAD_STATE newState) { this->_deadState = newState; };

bool Robot::operator==(const Robot& robot) const {
    return this->_id == robot._id;
}

void Robot::die() {
    this->_alive = false;
};

void Robot::move(const Position& newPos) {
    this->_pos = newPos;
};

int Robot::getRobotID() const {
    return this->_id;
};

Position Robot::getPosition() const {
    return this->_pos;
};

bool Robot::isAlive() const {
    return this->_alive;
};

Player::Player() { };

Player::Player(Position pos): _pos(pos), _alive(true) {};

void Player::die() {
    this->_alive = false;
};

void Player::move(const Position& newPos) {
    this->_pos = newPos;
};

Position Player::getPosition() const {
    return this-> _pos;
};

bool Player::isAlive() const {
    return this-> _alive;
};