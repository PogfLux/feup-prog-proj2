#pragma once

#include <vector>
#include "./entities.h"

class Maze {

    public:
        Maze(std::vector<Post> fences);

    private:
        std::vector<Post> fences;
};

class Post {
    
    public:
        Post(Position pos, bool isElectric);   

    private:
        Position pos;
        bool isElectric;

};

class Game {
    
    public:
        Game(Player player, Maze maze, std::vector<Robot> robots);

    private:
        Player player;
        Maze maze;
        std::vector<Robot> robots;
        
};