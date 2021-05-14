#pragma once

struct Position {

    int x, y;
};

class Robot {
    Robot(Position pos, int id, bool isAlive);

};

class Player {
    Player(Position pos, bool isAlive);

};