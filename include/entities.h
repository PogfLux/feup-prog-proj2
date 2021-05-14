#pragma once

struct Position {

    int x, y;
};

class Robot {
    public:
        Robot(Position pos, bool isAlive);
        void die();
        void move(Position newPos);
        int getRobotID() const; 
        Position getPosition() const;
        bool isAlive() const;


    private:
        Position pos;
        int id;
        bool isAlive;
        int setRobotID();
};

class Player {
    public:
        Player(Position pos, bool isAlive);
        void die();
        void move(Position newPos);
        Position getPosition() const;
        bool isAlive() const;


    private:
        Position pos;
        bool isAlive;
};