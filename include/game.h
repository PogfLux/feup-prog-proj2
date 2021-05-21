#pragma once

#include <vector>
#include "./entities.h"

class Post {
    
    public:
        Post(Position pos, bool electric);
        void setElectric(bool newState);
        Position getPosition() const;
        bool isElectric() const;

    private:
        Position _pos;
        bool _electric;

};

class Maze {

    public:
        Maze(std::vector<Post> fences);

    private:
        std::vector<Post> _fences;
};

class Game {
    
    public:
        Game(Player player, Maze maze, std::vector<Robot> robots);
        Player getPlayer() const;
        Maze getMaze() const;
        std::vector<Robot> getRobots() const;

    private:
        Player _player;
        Maze _maze;
        std::vector<Robot> _robots;
        
};