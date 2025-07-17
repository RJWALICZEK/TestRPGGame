#pragma once
#include "mob.h"
#include "map.h"

class Game {
  private:
    Mob *player;
    std::vector<Mob*>enemies;
    bool running;
    GameMap *map;

  public:
    Game(bool running = true);
    void gameLoop();
    void combat();
    void event();
    void showMainMenu();
    void startGame();
    void endGame();
  void kill();
  ~Game();
};