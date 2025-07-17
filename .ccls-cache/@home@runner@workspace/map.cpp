#include "map.h"
#include "game.h"
#include "functions.h"


GameMap::GameMap(Game* game) : game(game), playerX(3), playerY(2) {
  grid = {
    {'.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','P','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','E','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
  };
}
void GameMap::displayMap() {
  for (const auto &row : grid) {
    for (char c : row) {
      std::cout << c << ' ';
    }
    std::cout << '\n';
  }
}
void GameMap::movePlayer(char direction) {
    int newX = playerX;
    int newY = playerY;

    switch(direction) {
        case 'w': newY--; break;
        case 's': newY++; break;
        case 'a': newX--; break;
        case 'd': newX++; break;
        case 'q': break;
        default: return;
    }

  
    if (newY < 0 || newY >= grid.size() || newX < 0 || newX >= grid[0].size()) {
        std::cout << "\033[1;33mOut of bounds!\033[0m\n";
        sleep(600);
        return;
    }

    
    if (grid[newY][newX] == 'E') {
        std::cout << "\033[1;31mEncountered an enemy! Starting combat...\033[0m\n";
        sleep(1000);
        game->event();
    }

   
    grid[playerY][playerX] = '.'; // stara pozycja
    playerX = newX;
    playerY = newY;
    grid[playerY][playerX] = 'P'; // nowa pozycja
}
