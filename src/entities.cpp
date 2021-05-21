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

inline bool operator==(const Position& lhs, const Position& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

Robot::Robot(Position pos, bool alive) : _pos(pos), _alive(alive) { 
    this->_id = Robot::setRobotID();
};

inline int Robot::setRobotID() {
    static int id = 1;

    return id++;
};

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

Player::Player(Position pos, bool alive): _pos(pos), _alive(alive) {};

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