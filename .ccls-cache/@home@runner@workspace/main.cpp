#include "mob.h"
#include "game.h"
#include "map.h"
#include "items.h"
#include <iostream>

int main() { 
 
Game *game = new Game(true);
  game->gameLoop();
  delete game;


 /* Items inventory;
  inventory.listItems();
*/

  return 0;
}