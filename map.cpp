#include "map.h"
#include "functions.h"
#include "game.h"
#include "gameMaps.h"

GameMap::GameMap(Game *game, int idMap) : game(game), playerX(3), playerY(2) {
  for (auto &m : gameMaps) {
    if (m.id == idMap) {
      grid = m.grid;
      playerX = m.playerX;
      playerY = m.playerY;
      break;
    }
  }
  // Zabezpieczenie: jeśli nie znaleziono mapy, domyślnie pusta
  if (grid.empty()) {
    grid = std::vector<std::vector<char>>(5, std::vector<char>(5, '.'));
  }

  grid[playerY][playerX] = 'P'; // ustaw pozycję gracza
  flagEnemyStatus = true;
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
  std::cout << "[LOG] movePlayer('" << direction << "')\n";
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
    std::cout << "[LOG] movePlayer end – player at " << playerX << "," << playerY << "\n";
  }

  if (newY < 0 || newY >= grid.size() || newX < 0 || newX >= grid[0].size()) {
    std::cout << "\033[1;33mOut of bounds!\a\033[0m\n";
    sleep(600);
    return;
  }
  char targetTile = grid[newY][newX];
  if (targetTile == 'T' || targetTile == '#' || targetTile == '~') {
    std::cout << "\033[1;31mYou can't walk there!\a\033[0m\n";
    sleep(800);
    return;
  }
  if (targetTile == '>' || targetTile == '<' || targetTile == 'V' || targetTile == '^') {
    std::cout << "\033[1;33mYou found a door!\033[0m\n";
    sleep(600);

    int targetMapId = -1;
    const Maps* currentMap = nullptr;

    for (const auto& m : gameMaps) {
      if (m.id == game->getMapId()) {
        currentMap = &m;
        break;
      }
    }

    if (!currentMap) {
      std::cerr << "[ERROR] Current map not found!\n";
      return;
    }

    // Wybierz odpowiedni escapeId
    switch (targetTile) {
      case '>': targetMapId = currentMap->escapeIdA; break;
      case '<': targetMapId = currentMap->escapeIdB; break;
      case 'V': targetMapId = currentMap->escapeIdC; break;
      case '^': targetMapId = currentMap->escapeIdD; break;
    }

    if (targetMapId >= 0) {
      game->changeMap(targetMapId);
    } else {
      std::cout << "This door leads nowhere...\n";
      sleep(500);
    }

    return; // koniec wykonania, nie przechodzimy dalej
  }

  // Wydarzenia
  if (targetTile == 'E') {
    game->event("combat");

    if (game->getEnemies().empty() && !flagEnemyStatus) {
      grid[newY][newX] = '.'; // usunięcie wroga
      setTrueEnemyStatus();
    } else if (flagEnemyStatus) {
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
void GameMap::setFalseEnemyStatus() { flagEnemyStatus = false; }
void GameMap::setTrueEnemyStatus() { flagEnemyStatus = true; }
