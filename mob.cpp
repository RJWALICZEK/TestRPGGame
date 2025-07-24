#include "mob.h"
#include "items.h"
#include <iostream>
#include "functions.h"

Mob::Mob(std::string name, int hp, int dmg, int ap, int exp, int lvl)
: name(name), hp(hp), dmg(dmg), ap(ap), exp(exp), lvl(lvl),
  inventory(new Items()), equipedWeapon(nullptr), equipedArmor(nullptr) {}

std::string Mob::getName() const { return this->name; }

bool Mob::isAlive() const { return (this->hp > 0); }

void Mob::attack(Mob &target) {
  int dmg = this->dmg - (target.ap * 2);
  target.hp -= dmg;

  std::cout << "\033[1;31m" << this->name << "\033[0m attacks "
            << "\033[1;34m" << target.name << "\033[0m and deals "
            << "\033[1;33m" << dmg << " damage\033[0m.\n";

  if (target.isAlive()) {
    std::cout << "  → \033[1;34m" << target.name << "\033[0m still has "
              << "\033[1;32m" << target.hp << " HP\033[0m left.\n";
  } else {
    std::cout << "\033[1;34m" << target.name
              << "\033[0m \033[1;31mfell to the ground and died.\033[0m\n";
    this->exp += 40;

    if (this->exp >= 100) {
      this->lvlUp();
    }
  }
}

void Mob::getInfo() {
  std::cout << "[DEBUG] Before getInfo()\n";
  std::cout << "Name: \033[1;31m" << this->name << "\033[0m \tLvl: \033[1;31m" << this->lvl << "\033[0m\t";
    if (equipedWeapon)
      std::cout << "\tWeapon: \033[1;31m" << equipedWeapon->name << "\033[0m\t\n";
    else
      std::cout << "\n";
   
           std::cout << "HP: \033[1;32m" << this->hp << "\033[0m";
             if (equipedArmor)
               std::cout << "\t\t\t\t\tArmor: \033[1;31m" << equipedArmor->name << "\033[0m\t\n";
             else
               std::cout << "\n";
           std::cout << "Damage: \033[1;33m" << this->dmg << "\033[0m.\n"
            << "Armor: " << this->ap << std::endl;
}
void Mob::lvlUp() {
  this->lvl++;
  this->hp += 10;
  this->dmg += 5;
  this->ap += 2;
  this->exp = 0;
  std::cout << "\033[1;33m" << this->name << " has leveled up to level "
            << this->lvl << "!\033[0m. \n"
            << std::endl;
}

int Mob::getHp() const { return this->hp; }
void Mob::setHp(int value) { this->hp += value; }
void Mob::getItems() {
  (void)system("clear");
  std::cout << "=== YOUR INVENTORY ===\n";
  showPlayerInventory();
  std::cout << "\nChoose an item by ID to equip or use (0 to cancel): ";
  int choice;
  std::cin >> choice;

  if (choice == 0) {
    return; // Anulowanie wyboru
  }

  Item *selectedItem = getItemFromInventory(choice);

  if (selectedItem) {
    if (selectedItem->dmgBoost > 0 || selectedItem->apBoost > 0) {
      std::cout << "Would you like to equip this item? (y/n): ";
      char equipChoice;
      std::cin >> equipChoice;
      if (equipChoice == 'y') {
        if (selectedItem->dmgBoost > 0) {
          equipWeapon(selectedItem);
        } else if (selectedItem->apBoost > 0) {
          equipArmor(selectedItem);
        }
      }
    } else if (selectedItem->hpBoost > 0) {
      std::cout << "Would you like to use this potion? (y/n): ";
      char useChoice;
      std::cin >> useChoice;
      if (useChoice == 'y') {
        usePotion(selectedItem);
      }
    }
  } else {
    std::cout << "Item not found!\n";
  }
}

void Mob::equipWeapon(Item *weapon) {
  equipedWeapon = weapon;
  this->dmg += weapon->dmgBoost;
  std::cout << "Equiped weapon " << weapon->name << " **Press any button** "
            << std::endl;
}
void Mob::equipArmor(Item *armor) {
  equipedArmor = armor;
  this->ap += armor->apBoost;
  std::cout << "Equiped armor " << armor->name << " **Press any button** "
            << std::endl;
}
void Mob::usePotion(Item *potion) {
  hp += potion->hpBoost;
  if (potion->lvlBoost > 0) {
    lvlUp();
  }
  std::cout << "Used potion : " << potion->name << " **Press any button** "
            << std::endl;
  removeItemFromInventory(potion->id);
}

void Mob::addItemToInventory(Item *item) {
  if (item != nullptr) {
    playerInventory.push_back(item);
    std::cout << "Added " << item->name
              << " to inventory! **Press any button**\n";
    getChar();
  }
}

void Mob::removeItemFromInventory(int itemId) {
  for (auto it = playerInventory.begin(); it != playerInventory.end(); ++it) {
    if ((*it)->id == itemId) {
      std::cout << "Removed " << (*it)->name << " from inventory.\n";
      playerInventory.erase(it);
      break;
    }
  }
}

void Mob::showPlayerInventory() {
  if (playerInventory.empty()) {
    std::cout << "Your inventory is empty.\n";
    return;
  }

  for (auto item : playerInventory) {
    std::cout << "\n\e[1;93mID: " << item->id << " | " << item->name
              << "\033[0m\n";
    std::cout << "Info: " << item->description << "\n";
    std::cout << "Dmg: +" << item->dmgBoost << " | Ap: +" << item->apBoost
              << " | Hp: +" << item->hpBoost << " | Lvl: +" << item->lvlBoost
              << "\n";
  }
}

Item *Mob::getItemFromInventory(int itemId) {
  for (auto item : playerInventory) {
    if (item->id == itemId) {
      return item;
    }
  }
  return nullptr;
}
