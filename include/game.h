#pragma once

#include <vector>
#include <string>

#include "./entities.h"

#define MAZE_FILE_NAME(mazeNumber) std::string("MAZE_") + ((mazeNumber < 10) ? "0" : "") + std::to_string(mazeNumber) + ".TXT"

class Post {
    
    public:
        Post();
        Post(Position pos, bool electric);
        void setElectric(bool newState);
        Position getPosition() const;
        bool isElectric() const;

    private:
        Position _pos;
        bool _electric;
        char _fenceType;
};

class Maze {

    public:
        Maze();
        Maze(int numCols, int numRows);

    private:
        std::vector<Post> _posts;
        int _numCols;
        int _numRows;
};

class Game {
    
    public:
        Game();
        Player getPlayer() const;
        Maze getMaze() const;
        bool over() const;
        std::string pickMaze();
        bool mazePicked() const;
        void createMaze(std::string& mazeFileName) const;
        std::vector<Robot> getRobots() const;

    private:
        Player _player;
        Maze _maze;
        std::vector<Robot> _robots;
        bool _gameOver;
        bool _mazePicked;
        
};