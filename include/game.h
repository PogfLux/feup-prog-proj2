#pragma once

#include <vector>
#include <string>

#include "./entities.h"

#define MAZE_FILE_NAME(mazeNumber) std::string("MAZE_") + ((mazeNumber < 10) ? "0" : "") + std::to_string(mazeNumber) + ".TXT"

/**
 * @brief represents an exit of the game.
 * 
 */
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
        int getNumRows() const;
        int getNumCols() const;
        std::vector<Exit> getExits() const;
        std::vector<Post> getPosts() const;
        bool collidesWithNonElectricPost(const Position& pos) const;

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
        Player getPlayer();
        Maze getMaze() const;
        bool over() const;
        int pickMaze();
        bool mazePicked() const;
        void createMaze(int mazeNumber);
        std::vector<Robot>& getRobots();
        char pollPlayerMovement();
        void getEntityPositionsInBoard();
        void printBoard();
        void setMaze(const Maze& maze);
        bool isValidPlayerPosition(const Position& newPos);
        Position getNewPlayerPosition(char playerMove);
        void moveRobots();
        Position getRobotMove(const Robot& robot);
        void checkGameStatus();
        void movePlayer(const Position& newPos);

    private:
        Player _player;
        Maze _maze;
        std::vector<Robot> _robots;
        bool _gameOver;
        bool _mazePicked;
        std::vector<char> _boardChars; // use this to store the chars when printing the board

        // define as 'static const' as to create it only once, and not modify it after creation.
        static const std::vector<char> validMoves; 
        
};