#pragma once
#include "map.h"
#include "items.h"
#include "mob.h"
#include <vector>

class Game {
private:
  Mob *player;
  Mob *enemy;
  std::vector<Mob *> enemies;
  bool running;
  bool inGame;
  GameMap *map;

public:
  Game(bool running = true);
  void gameLoop();
  void combat(int enemiesCount);
  void event(std::string eventType);
  void startGame();
  void endGame();
  const std::vector<Mob *> &getEnemies() const { return enemies; }
  ~Game();
};