#include "mapData.h"
#include "map.h"
#include "functions.h"
#include "game.h"



GameMap::GameMap(Game* game, int startId) : game(game), playerX(1), playerY(1), id(startId) {
    flagEnemyStatus = true;
    loadMapById(id);
}

void GameMap::displayMap() {
  for (const auto &row : grid) {
    for (char c : row) {
      switch (c) {
      case 'P':
        std::cout << "\e[1;32m" << c << " \033[0m"; // Jasnozielony - gracz
        break;
      case 'E':
        std::cout << "\033[1;31m" << c << " \033[0m"; // Czerwony - wróg
        break;
        case '*':
        std::cout << "\e[1;35m" << c << " \033[0m"; // Czerwony - wróg
        break;
      case 'T':
        std::cout << "\033[32m" << c << " \033[0m"; // Zielony - drzewa
        break;
      case '#':
        std::cout << "\033[33m" << c << " \033[0m"; // Żółty - krzaki
        break;
      case '~':
        std::cout << "\033[34m" << c << " \033[0m"; // Niebieski - woda
        break;
      case '.':
        std::cout << "\033[0m" << c << " "; // Domyślny kolor - trawa
        break;
      default:
        std::cout << c << ' '; // Pozostałe znaki bez koloru
        break;
      }
    }
    std::cout << '\n';
  }
}
void GameMap::movePlayer(char direction) {
  int newX = playerX;
  int newY = playerY;

  switch (direction) {
  case 'w':
    newY--;
    break;
  case 's':
    newY++;
    break;
  case 'a':
    newX--;
    break;
  case 'd':
    newX++;
    break;
  default:
    return;
  }

  if (newY < 0 || newY >= grid.size() || newX < 0 || newX >= grid[0].size()) {
    std::cout << "\033[1;33mOut of bounds!\033[0m\n";
    sleep(600);
    return;
  }
  char targetTile = grid[newY][newX];
  if (targetTile == 'T' || targetTile == '#' || targetTile == '~') {
    std::cout << "\033[1;31mYou can't walk there!\033[0m\n";
    sleep(800);
    return;
  }

  // Wydarzenia
  if (targetTile == 'E') {
    game->event("combat");
    
    if (game->getEnemies().empty() && !flagEnemyStatus) {
      grid[newY][newX] = '.'; // usunięcie wroga
      setTrueEnemyStatus();
    } 
    else if(flagEnemyStatus) {
      grid[newY][newX] = 'E';
      return; // jeśli wróg przeżył, nie poruszaj się
    }
    
    
  } else if (targetTile == '*') {
    game->event("treasure");
    grid[newY][newX] = '.'; // usunięcie skarbu
  }

  // Przeniesienie gracza
  grid[playerY][playerX] = '.'; // stara pozycja
  playerX = newX;
  playerY = newY;
  grid[playerY][playerX] = 'P'; // nowa pozycja
}
void GameMap::setFalseEnemyStatus() {
    flagEnemyStatus = false;
}
void GameMap::setTrueEnemyStatus() {
    flagEnemyStatus = true;
}

void GameMap::loadMapById(int newId) {
    id = newId;
    if (newId >= 0 && newId < gameMaps.size()) {
        const MapInfo& map = gameMaps[id];
        grid = map.grid;
        
        std::cout << "Loading map: " << map.name << std::endl;
        std::cout << "Map size: " << grid.size() << "x" << (grid.empty() ? 0 : grid[0].size()) << std::endl;
        
        // Find a suitable starting position (first empty spot or X)
        bool placed = false;
        for (int y = 1; y < grid.size() - 1 && !placed; y++) {
            for (int x = 1; x < grid[y].size() - 1 && !placed; x++) {
                if (grid[y][x] == '.' || grid[y][x] == 'X') {
                    playerX = x;
                    playerY = y;
                    grid[playerY][playerX] = 'P';
                    placed = true;
                    std::cout << "Player placed at: (" << x << ", " << y << ")" << std::endl;
                }
            }
        }
        
        // Fallback to (1,1) if no suitable position found
        if (!placed) {
            playerX = 1;
            playerY = 1;
            if (playerY < grid.size() && playerX < grid[playerY].size()) {
                grid[playerY][playerX] = 'P';
                std::cout << "Player placed at fallback position: (1, 1)" << std::endl;
            }
        }
    } else {
        std::cout << "Error: Invalid map ID " << newId << std::endl;
    }
}