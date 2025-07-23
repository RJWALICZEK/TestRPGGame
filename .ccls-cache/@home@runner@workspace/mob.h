#pragma once
#include "items.h"
#include <string>
#include <vector>


class Mob {
private:
  std::string name;
  int hp;
  int dmg;
  int ap;
  int exp;
  int lvl;
  Items *inventory;
  std::vector<Item*> playerInventory;

  Item *equipedWeapon;
  Item *equipedArmor;

public:
  Mob(std::string name = "default", int hp = 1, int dmg = 1, int ap = 1,
      int exp = 1, int lvl = 1);
  std::string getName() const;
  bool isAlive() const;
  void attack(Mob &target);
  void getInfo();
  void lvlUp();
  int getHp() const;
  void getItems();
  void setHp(int value);

  void equipWeapon(Item *weapon);
  void equipArmor(Item *armor);
  void usePotion(Item *potion);
  void addItemToInventory(Item* item);
  void removeItemFromInventory(int itemId);
  void showPlayerInventory();
  Item* getItemFromInventory(int itemId);
};