#pragma once
#include "map.h"


class Game;

#include <vector>
#include <iostream>

class GameMap {
    Game* game; 
    int playerX, playerY;
    std::vector<std::vector<char>> grid;
    bool flagEnemyStatus;

public:
    GameMap(Game* game);
    void displayMap();
    void movePlayer(char direction);
    void removeEnemy(int y, int x);
    void setFalseEnemyStatus();
    void setTrueEnemyStatus();

};
