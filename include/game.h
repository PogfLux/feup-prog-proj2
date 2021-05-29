//T10_G01

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
        /**
         * @brief Construct a new Post object.
         * 
         */
        Post();

        /**
         * @brief Construct a new Post object.
         * 
         * @param pos the post's position.
         * @param electric whether the post is electric or not.
         */
        Post(Position pos, bool electric);

        /**
         * @brief Set a post to either electric or not electric.
         * 
         * @param newState the state of the post.
         */
        void setElectric(bool newState);

        /**
         * @brief Get the Position of an object.
         * 
         * @return the object's position.
         */
        Position getPosition() const;

        /**
         * @brief Check if a Post is electric or not.
         * 
         * @return true if it's electric.
         * @return false if it's not electric.
         */
        bool isElectric() const;

    private:
        Position _pos;
        bool _electric;
        char _fenceType;
};

class Maze {

    public:
        /**
         * @brief Construct a new Maze object.
         * 
         */
        Maze();
        
        /**
         * @brief Construct a new Maze object.
         * 
         * @param numCols the number of collumns of this maze
         * @param numRows the number of rows of this maze
         * @param mazeNumber the number of this maze
         */
        Maze(int numCols, int numRows, int mazeNumber);

        /**
         * @brief Adds a new post to the maze.
         * 
         * @param p the post to add
         */
        void addPost(Post p);

        /**
         * @brief Adds a new exit to the maze.
         * 
         * @param e the exit to add
         */
        void addExit(Exit e);

        /**
         * @brief Returns the number of this maze.
         * 
         * @return the number of this maze
         */
        int getMazeNumber() const;

        /**
         * @brief Get the number of rows of this maze.
         * 
         * @return the number of rows
         */
        int getNumRows() const;

        /**
         * @brief Get the number of collumns of this maze.
         * 
         * @return the number of collumns
         */
        int getNumCols() const;

        /**
         * @brief Get the Exits of the maze.
         * 
         * @return a vector with the exits
         */
        std::vector<Exit> getExits() const;

        /**
         * @brief Returns all of the posts, eletric or not, of the maze.
         * 
         * @return 
         */
        std::vector<Post> getPosts() const;

        /**
         * @brief Checks to see if the given position representes a non eletric post.
         * 
         * @param pos the position to check
         * @return true if there is a non eletric post at the given position, false otherwise
         */
        bool collidesWithNonElectricPost(const Position& pos) const;

    private:

        std::vector<Post> _posts;
        int _mazeNumber;
        int _numCols;
        int _numRows;
        std::vector<Exit> _exits;
};

/**
 * @brief The Game class, whose objects are responsible for enforcing the rules of the game.
 * 
 */
class Game {
    
    public:
        /**
         * @brief Construct a new Game object.
         * 
         */
        Game();

        /**
         * @brief Get the Player object.
         * 
         * @return the game's player
         */
        Player getPlayer();

        /**
         * @brief Get the Maze object.
         * 
         * @return the games current maze
         */
        Maze getMaze() const;

        /**
         * @brief Checks if the game is over.
         * 
         * @return true if the game is ver, false otherwise
         */
        bool over() const;

        /**
         * @brief Picks a maze for the user to play.
         * 
         * @return the number of the maze chosen 
         */
        int pickMaze();

        /**
         * @brief Checks if the user has picked a maze.
         * 
         * @return true if the user has picked a maze, false otherwise
         */
        bool mazePicked() const;

        /**
         * @brief Create the maze from the sepcified maze number.
         * 
         * @param mazeNumber the number of the maze to play
         */
        void createMaze(int mazeNumber);

        /**
         * @brief Get the Robots of the game.
         * 
         * @return the robots in the game
         */
        std::vector<Robot>& getRobots();

        /**
         * @brief Polls input from the user in order to move the player.
         * 
         * @return the move the player inputted 
         */
        char pollPlayerMovement();

        /**
         * @brief Get the positions of every entity (player, posts, robots, exits) in the game.
         * 
         */
        void getEntityPositionsInBoard();

        /**
         * @brief Prints the current game's board.
         * 
         */
        void printBoard();

        /**
         * @brief Set the Maze object
         * 
         * @param maze the new maze
         */
        void setMaze(const Maze& maze);

        /**
         * @brief Checks if the given position is a valid player position.
         * 
         * @param newPos the new possible position of the player
         * @return true if the player can move to the given position, false otherwise
         */
        bool isValidPlayerPosition(const Position& newPos);

        /**
         * @brief Get the New Player Position
         * 
         * @param playerMove the mve to make
         * @return the new position according to the move chosen
         */
        Position getNewPlayerPosition(char playerMove);

        /**
         * @brief Moves all robots.
         * 
         */
        void moveRobots();

        /**
         * @brief Get the next move for the specified robot.
         * 
         * @param robot the robot whose move we want to generate
         * @return the new position of the given robot
         */
        Position getRobotMove(const Robot& robot);

        /**
         * @brief Moves the player to the new position, checking for win/lose conditions.
         * 
         * @param newPos the new position of the player
         */
        void movePlayer(const Position& newPos);

    private:
        Player _player;
        Maze _maze;
        std::vector<Robot> _robots;
        bool _gameOver;
        bool _mazePicked;
        std::vector<char> _boardChars; // use this to store the chars when printing the board

        // define as 'static const' in order to create it only once, and not modify it after creation.
        static const std::vector<char> validMoves; 
        
        /**
         * @brief Checks for robot-robot collisions
         * 
         * @param robot the robot to check for collisions
         * @param nextPos the possible new position of the robot
         * @return true if the robot would collide, false otherwise
         */
        bool robotToRobotCollision(Robot& robot, Position nextPos);

        /**
         * @brief Checks for robot collisions with the maze.
         * 
         * @param robot the robot to check for collisions
         * @param nextPos the possible new position of the robot
         * @return true if the robot would collide, false otherwise
         */
        bool robotToMazeCollision(Robot& robot, Position nextPos);
};