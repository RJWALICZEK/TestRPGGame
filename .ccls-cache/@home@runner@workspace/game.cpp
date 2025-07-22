#include "game.h"
#include "functions.h"
#include "items.h"
#include "map.h"
#include "mob.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

Game::Game(bool running) : player(nullptr), enemy(nullptr), running(running) {}

void Game::gameLoop() {
  while (running) {
    std::cout << "\n**Welcome to the game!**\n"
              << "1. Start Game\n"
              << "2. Exit\n";
    char input = getChar();

    switch (input) {
    case '1':
      inGame = true;
      startGame();
      break;
    case '2':
      running = false;
      break;
    default: {
      std::cout << "Invalid output, try again. \n";
    }
    }
  }
}

void Game::startGame() {
  std::cout << "Enter yout character name : ";
  std::string name;
  std::cin >> name;
  if (player) {
    delete player;
  }
  player = new Mob(name, 100, 30, 5, 0, 1);
  (void)system("clear");

  while (player->isAlive() && inGame) {
    if (map) {
      delete map;
    }
    map = new GameMap(this);

    char input;

    while (player->isAlive()) {
      player->getInfo();
      map->displayMap();
      std::cout << "Move (w/a/s/d) Inventory (i) Quit (q)\n";
      input = getChar();

      if (input == 'q') {
        inGame = false;
        std::cout << "Exiting to main menu... *Press any button*\n";
        getChar();
        (void)system("clear");
        break; // Exit to main menu
      } else if (input == 'i') {
        player->getItems();
        getChar();
        (void)system("clear");
      }

      map->movePlayer(input);

      (void)system("clear"); // Linux
    }
  }
  if (!player->isAlive() && !running) {
    std::cout << "Game over!\n";
    getChar();
    sleep(1200);
  }
}
void Game::combat(int enemiesCount) {
  // SPAWN PRZECIWNIKOW
  for (int i = 0; i < enemiesCount; i++) {
    enemies.push_back(new Mob("Goblin" + std::to_string(i + 1),
                              40 + (getRandomStat() * 2),
                              20 + (getRandomStat() * 2), 0, 1));
  }

  //--------------------

  while (player->isAlive() && !enemies.empty()) {
    // Gracz atakuje pierwszego żywego przeciwnika
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
      if ((*it)->isAlive()) {
        player->attack(**it);
        sleep(1200);
        // Usuń martwego przeciwnika
        if (!(*it)->isAlive()) {
          std::cout << "\033[1;32mYou have defeated " << (*it)->getName()
                    << "!\033[0m\n\n";
          delete *it;
          enemies.erase(it);
          map->setFalseEnemyStatus();
        }
        break;
      }
    }

    // Wszyscy żywi przeciwnicy atakują gracza
    for (Mob *enemy : enemies) {
      if (enemy->isAlive() && player->isAlive()) {
        enemy->attack(*player);
        sleep(1200);
        if (!player->isAlive()) {
          std::cout << "\033[1;31mYou have been defeated! *Press any "
                       "button*\033[0m\n";
          getChar();
          return;
        }
      }
    }
  }

  if (enemies.empty()) {
    std::cout << "\033[1;32mYou have defeated all enemies! *Press any "
                 "button*\033[0m\n\n";
    if (enemies.empty()) {
      std::cout << "\033[1;32mYou have defeated all enemies!\033[0m\n";

      // Nagroda - losowy przedmiot
      initRandom();
      Items itemDatabase;
      const auto &availableItems = itemDatabase.getItemMap();
      if (!availableItems.empty()) {
        int randomIndex = std::rand() % availableItems.size();
        Item *rewardItem =
            new Item(*availableItems[randomIndex]); // Kopia przedmiotu
        std::cout << "\033[1;33mYou found: " << rewardItem->name
                  << "!\033[0m\n";
        player->addItemToInventory(rewardItem);
      }

      std::cout << "*Press any button*\n";
      getChar();
    }
  }
}
void Game::event(std::string eventType) {
  if (player->isAlive() && running && eventType == "combat") {
    initRandom();
    int enemiesCount = getRandomEnemyCount();
    char input;

    enemiesCount > 1
        ? std::cout << "\033[1;31mYou encounter a group of enemies!\033[0m.\n"
        : std::cout << "\033[1;31mYou encounter an enemy!\033[0m.\n";
    sleep(900);
    std::cout << "What action will you take ?\n fight (f) run (r)\n ";
    input = getChar();
    switch (input) {
    case 'f': {
      combat(enemiesCount);
      break;
    }
    case 'r': {
      std::cout << "You ran away! *Press any button*\n";
      getChar();
      map->setTrueEnemyStatus();
      return;
      break;
    }
    }

  } else if (player->isAlive() && eventType == "treasure") {
    std::cout << "You found treasure!\n";
    initRandom();
    Items itemDatabase;
    const auto &availableItems = itemDatabase.getItemMap();
    if (!availableItems.empty()) {
      int randomIndex = std::rand() % availableItems.size();
      Item *treasureItem = new Item(*availableItems[randomIndex]);
      std::cout << "You also found: " << treasureItem->name << "!\n";
      player->addItemToInventory(treasureItem);
    }

    sleep(1200);
  }
}
void Game::endGame() {
  ;
  delete player;
  player = nullptr;
}

Game::~Game() {
  if (player) {
    delete player;
  }
  for (Mob *enemy : enemies) {
    delete enemy;
  }
  if (enemy) {
    delete enemy;
  }
  enemies.clear();
  if (map) {
    delete map;
  }
}