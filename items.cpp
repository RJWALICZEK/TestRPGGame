#include "items.h"
#include <iostream>

Items::Items() {
  //weapons 
  Item* weapon_club = new Item{"Club", 1, "A rooten wood club", 5, 0, 0, 0};
  Item* weapon_sword_iron = new Item{"Iron Sword", 2, "A rusty iron sword", 10, 0, 0, 0};
  Item* weapon_axe_steel = new Item{"Steel Axe", 3, "A sharp steel axe", 15, 0, 0, 0};
  Item* weapon_sword_mithril = new Item{"MIthril Sword", 4, "A magical powerfull sword", 20, 5, 0, 0};
  Item* weapon_dagger_iron = new Item{"Iron dagger", 5, "A short rusty blade", 5, 0, 0, 0};
  Item* weapon_mace = new Item{"Heavy Mace", 6, "Heavy mace , good for blow enemies head", 5, 0, 0, 0};
  Item* weapon_staff = new Item{"Long staff", 7, "Long piece of wooden stick", 5, 0, 0, 0};
  Item* weapon_pickaxe = new Item{"Heavy pickaxe", 8, "Better use like a tool, not weapon", 5, 0, 0, 0};
  //armors
  Item* armor_rags = new Item{"Rags", 9, "Dirty thick material shirt", 0, 5, 0, 0};
  Item* armor_la = new Item{"Leather Armor", 10, "A cheap leather armor", 0, 5, 0, 0};
  Item* armor_ma = new Item{"Mail Armor", 11, "A medium mail armor", 0, 10, 0, 0};
  Item* armor_pa = new Item{"Plate Armor", 12, "A heavy plate armor", 0, 15, 0, 0};
  //potions
  Item* potion_hp_s = new Item{"Small Hp Potion", 13, "A small hp potion", 0, 0, 20, 0};
  Item* potion_hp_m = new Item{"Medium Hp Potion", 14, "A medium hp potion", 0, 0, 60, 0};
  Item* potion_hp_l = new Item{"Large Hp Potion", 15, "A large hp potion", 0, 0, 100, 0};
  Item* potion_lvlUp = new Item{"Lvl Up Potion", 16, "A potion that levels you up", 0, 0, 0, 1};

  //intems init
  addItem(weapon_club);
  addItem(weapon_sword_iron);
  addItem(weapon_axe_steel);
  addItem(weapon_sword_mithril);
  addItem(weapon_dagger_iron);
  addItem(weapon_mace);
  addItem(weapon_staff);
  addItem(weapon_pickaxe);
  addItem(armor_rags);
  
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


