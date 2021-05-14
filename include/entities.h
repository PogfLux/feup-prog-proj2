

/**
 * @file entities.h
 * @author Nuno Pereira (up202007865@edu.fe.up.pt)
 * @author Luís Osório (up202004653@edu.fe.up.pt)
 * @brief entity classes for main.cpp 
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

/**
 * @brief position structure
 * 
 */
struct Position
{
    int x, y;
};

/**
 * @brief class for Robot entities
 * 
 */

class Robot
{
    Robot(Position pos, int id, bool isAlive);
};


/**
 * @brief class for Player entity
 * 
 */

class Player
{
    Player(Position pos, bool isAlive);
};