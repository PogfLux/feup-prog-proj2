#pragma once

#include <vector>
#include <string>

#include "./entities.h"

#define MAZE_FILE_NAME(mazeNumber) std::string("MAZE_") + ((mazeNumber < 10) ? "0" : "") + std::to_string(mazeNumber) + ".TXT"

using Exit = Position;

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
        Maze(int numCols, int numRows, int mazeNumber);
        void addPost(Post p);
        void addExit(Exit c);
        int getMazeNumber() const;

    private:
        std::vector<Post> _posts;
        int _mazeNumber;
        int _numCols;
        int _numRows;
        std::vector<Exit> _exits;
};

class Game {
    
    public:
        Game();
        Player getPlayer() const;
        Maze getMaze() const;
        bool over() const;
        int pickMaze();
        bool mazePicked() const;
        void createMaze(int mazeNumber);
        std::vector<Robot> getRobots() const;
        char pollPlayerMovement();

    private:
        Player _player;
        Maze _maze;
        std::vector<Robot> _robots;
        bool _gameOver;
        bool _mazePicked;
        
        // define as 'static const' as to create it only once, and not modify it after creation.
        static const std::vector<char> validMoves; 
        
};