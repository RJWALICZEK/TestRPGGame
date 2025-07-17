#pragma once

class Game; // ← To jest forward declaration!

#include <vector>
#include <iostream>

class GameMap {
    Game* game; // ← teraz kompilator zna, że taki typ istnieje
    int playerX, playerY;
    std::vector<std::vector<char>> grid;

public:
    GameMap(Game* game);
    void displayMap();
    void movePlayer(char direction);
};