#pragma once

struct Position {
    int x, y;
};

inline bool operator==(const Position& lhs, const Position& rhs);

class Robot {
    
    public:
        Robot();
        Robot(Position pos, bool alive);
        void die();
        void move(const Position& newPos);
        int getRobotID() const; 
        Position getPosition() const;
        bool isAlive() const;
        inline bool operator==(const Robot& other) const;

    private:
        enum DEAD_STATE {
            STUCK,
            DEAD
        };

        Position _pos;
        int _id;
        DEAD_STATE _deadState;
        bool _alive;
        static inline int setRobotID();
};

class Player {

    public:
        Player();
        Player(Position pos, bool alive);
        void die();
        void move(const Position& newPos);
        Position getPosition() const;
        bool isAlive() const;

    private:
        Position _pos;
        bool _alive;
};