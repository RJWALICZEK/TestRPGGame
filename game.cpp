#include "game.h"
#include "mob.h"
#include "map.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "functions.h"

Game::Game( bool running) : player(nullptr), enemy(nullptr), running(running) {}

void Game::gameLoop() {
  while (running) {
    std::cout << "\n**Welcome to the game!**\n" << "1. Start Game\n" << "2. Exit\n";
    int choice;
   std::cin >> choice;
    switch (choice) {
      case 1:
        startGame();
        break;
      case 2:
        running = false;
        break;
      default : {
        std::cout << "Invalid output, try again. \n"; 
      }
    }
  }
}

void Game::startGame() {
  std::cout << "Enter yout character name : ";
  std::string name;
  std::cin >> name;
  if(player) {
    delete player;
  }
  player = new Mob(name, 100, 30, 5 ,0 , 1);
  (void) system("clear");
   
  while(player->isAlive() && running) {
    if(map) {
      delete map;
    }
    map =  new GameMap(this);
    
    //enemies spawn
    enemies.push_back(new Mob("Goblin 1", 50, 28, 0, 1));
    enemies.push_back(new Mob("Goblin 2", 50, 28, 0, 1));
    
    char input;

    while(player->isAlive()) {
       player->getInfo();
        map->displayMap();  
        std::cout << "Move (w/a/s/d) Quit (q) >> \n";
        input = getChar();
        map->movePlayer(input);  

        (void) system("clear"); // Linux
    }
  }
  if (!player->isAlive() && !running) {
    std::cout << "Game over!\n";
    sleep(1200);
  }
}
void Game::combat() {
    std::cout << "\033[1;33mYou encounter an enemy!\033[0m.\n";

    while (player->isAlive() && enemy->isAlive()) {
        player->attack(*enemies);

        if (enemy->isAlive()) {
            enemy->attack(*player);
            if (!player->isAlive()) {
                std::cout << "\033[1;31mYou have been defeated!\033[0m\n";
                sleep(1700);
                delete player;
                player = nullptr;
                return;
            }
        } else {
            std::cout << "\033[1;32mYou have defeated the enemy!\033[0m\n\n";
            sleep(1700);
        }

        sleep(1700);
    }

    delete enemy;
    enemy = nullptr;
}
void Game::event() { 
  if(player->isAlive() && running)
      {
        combat();
      }
  }
void Game::endGame() {;
  delete player;
  player = nullptr;
}


Game::~Game() { 
  if(player) {
    delete player;
  }
  for (Mob* enemy: enemies) {
    delete enemy;
  }
  enemies.clear();
  if (map) {
    delete map;
  }
}