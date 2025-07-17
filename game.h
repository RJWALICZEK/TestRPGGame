#pragma once
#include "map.h"
#include "mob.h"
#include <vector>

class Game {
private:
  Mob *player;
  Mob *enemy;
  std::vector<Mob *> enemies;
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
  const std::vector<Mob *> &getEnemies() const { return enemies; }
  ~Game();
};