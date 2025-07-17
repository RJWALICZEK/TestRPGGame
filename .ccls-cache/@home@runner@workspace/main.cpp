#include "mob.h"
#include "game.h"
#include "map.h"
#include <iostream>

int main() { 
  
Game *game = new Game(true);
  game->gameLoop();
  delete game;
  return 0;
}