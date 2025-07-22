#pragma once
#include <string>
#include <vector>

struct Item {
  std::string name;
  int id;
  std::string description;
  int dmgBoost;
  int apBoost;
  int hpBoost;
  int lvlBoost;

};

class Items {
private:
  std::vector<Item*> itemMap;
public:
  Items();
  ~Items();
  void addItem(Item*);
  const std::vector<Item*>& getItemMap() const;
  void listItems();
  void shortListItems();
};

