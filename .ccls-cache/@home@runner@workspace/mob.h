#pragma once
#include <string>

class Mob {
  private:
    std::string name;
    int hp;
    int dmg;
    int ap;
    int exp;
    int lvl;
  
  public:
    Mob(std::string name = "default", int hp = 1, int dmg = 1, int ap = 1, int exp = 1,         int lvl = 1);
    std::string getName() const;
    bool isAlive() const;
    void attack(Mob &target);
    void getInfo();
   void lvlUp();
};