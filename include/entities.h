//T10_G01

#pragma once

/**
 * @brief a position every entity in the game has
 * 
 */
struct Position {
    int x, y;
};

/**
 * @brief CHecks if the two positions are equal.
 * 
 * @param lhs the first position
 * @param rhs the second position
 * @return true if the positions are the same, false otherwise
 */
inline bool operator==(const Position& lhs, const Position& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
};

/**
 * @brief The Robot class, defining the enemies in the game.
 * 
 */
class Robot {
    
    public:

        /**
         * @brief The state of the robot when he dies.
         * 
         */
        enum DEAD_STATE {
            STUCK,
            DEAD
        };
        
        /**
         * @brief Construct a new Robot object.
         * 
         */
        Robot();

        /**
         * @brief Construct a new Robot object.
         * 
         * @param pos The position of the robot
         * @param alive Weather the robot is alive or not
         */
        Robot(Position pos, bool alive);

        /**
         * @brief Kill this robot
         * 
         */
        void die();

        /**
         * @brief Moves the robot to the given position.
         * 
         * @param newPos the new position of the player
         */
        void move(const Position& newPos);

        /**
         * @brief Get the Robot ID object.
         * 
         * @return the id of this robot
         */
        int getRobotID() const; 

        /**
         * @brief Get the Position object
         * 
         * @return the position of this robot
         */
        Position getPosition() const;

        /**
         * @brief Checks if the robot is alive.
         * 
         * @return true if the robot is alive, false otherwise
         */
        bool isAlive() const;

        /**
         * @brief Checks if the other robot is the same as us.
         * 
         * @param other the rbot to verify against us
         * @return true 
         */
        bool operator==(const Robot& other) const;

        /**
         * @brief Set the Dead State object.
         * 
         * @param newState the new death state of this robot
         */
        void setState(DEAD_STATE newState);

    private:

        Position _pos;
        int _id;
        DEAD_STATE _deadState;
        bool _alive;

        /**
         * @brief Set the Robot ID object
         * 
         * @return the id of this robot
         */
        static inline int setRobotID();
};

/**
 * @brief The player object, controlled by the user.
 * 
 */
class Player {

    public:
        /**
         * @brief Construct a new Player object.
         * 
         */
        Player();

        /**
         * @brief Construct a new Player object.
         * 
         * @param pos the position of the player 
         */
        Player(Position pos);

        /**
         * @brief Kill the player.
         * 
         */
        void die();

        /**
         * @brief Moves the player to the given position
         * 
         * @param newPos the new position of the player
         */
        void move(const Position& newPos);

        /**
         * @brief Get the Position object of the player
         * 
         * @return the position of the player
         */
        Position getPosition() const;

        /**
         * @brief Checks if the player is alive or not.
         * 
         * @return true if the player is alive, false otherwise
         */
        bool isAlive() const;

    private:
        Position _pos;
        bool _alive;
};