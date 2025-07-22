#include "items.h"
#include <iostream>

Items::Items() {
  //weapons 
  Item* sword_cs = new Item{"Club", 1, "A rooten wood club", 5, 0, 0, 0};
  Item* sword_is = new Item{"Iron Sword", 2, "A rusty iron sword", 10, 0, 0, 0};
  Item* sword_sa = new Item{"Steel Axe", 3, "A sharp steel axe", 15, 0, 0, 0};
  Item* sword_ms = new Item{"MIthril Sword", 4, "A magical powerfull sword", 20, 5, 0, 0};
  //armors
  Item* armor_la = new Item{"Leather Armor", 5, "A cheap leather armor", 0, 5, 0, 0};
  Item* armor_ma = new Item{"Mail Armor", 6, "A medium mail armor", 0, 10, 0, 0};
  Item* armor_pa = new Item{"Plate Armor", 7, "A heavy plate armor", 0, 15, 0, 0};
  //potions
  Item* potion_hp_s = new Item{"Small Hp Potion", 8, "A small hp potion", 0, 0, 20, 0};
  Item* potion_hp_m = new Item{"Medium Hp Potion", 9, "A medium hp potion", 0, 0, 60, 0};
  Item* potion_hp_l = new Item{"Large Hp Potion", 10, "A large hp potion", 0, 0, 100, 0};
  Item* potion_lvlUp = new Item{"Lvl Up Potion", 11, "A potion that levels you up", 0, 0, 0, 1};

  //intems init
  addItem(sword_cs);
  addItem(sword_is);
  addItem(sword_sa);
  addItem(sword_ms);
  addItem(armor_la);
  addItem(armor_ma);
  addItem(armor_pa);
  addItem(potion_hp_s);
  addItem(potion_hp_m);
  addItem(potion_hp_l);
  addItem(potion_lvlUp);
  
  
}

Items::~Items() {
  for (auto item : itemMap) {
    delete item;
  }
  itemMap.clear();
}

void Items::addItem(Item *item) {
  itemMap.push_back(item);
}

void Items::listItems() {
  for( auto item : itemMap) {
    std::cout << "\n\e[1;93mID   : " << item->id << " | " << item->name << "\033[0m. \nInfo : " << item->description << "\nDmg  : +" << item->dmgBoost << "\nAp   : +" << item->apBoost << "\nHp   : +" << item->hpBoost << "\nLvl  : +" << item->lvlBoost << std::endl; 
  }
}

void Items::shortListItems() {
  for( auto item : itemMap)
    {
      std::cout << "\n\e[1;93mID   : " << item->id << " | " << item->name << "\033[0m. \n";
    }
}

const std::vector<Item*>& Items::getItemMap() const {
  return itemMap;
} 


