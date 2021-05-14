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
#include <vector>
#include "./entities.h"


/**
 * @brief class for the board maze
 * 
 */

class Maze
{
    Maze(std::vector <Post> fences);
};

/**
 * @brief class for the board's fences
 * 
 */

class Post
{
    Post(Position pos, bool isElectric);
};

/**
 * @brief class for the game board
 * 
 */

class Game
{
    Game(Maze maze, Player player, std::vector <Robot> robots);
};