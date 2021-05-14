#pragma once

#include <vector>
#include "./entities.h"

class Maze
{
    Maze(std::vector <Post> fences);

};

class Post
{
    Post(Position pos, bool isElectric);   

};

class Game
{
    Game(Player player, Maze maze, std::vector<Robot> robots);

};