#include "mob.h"
#include <iostream>

Mob::Mob (std::string name, int hp, int dmg, int ap, int exp, int lvl) 
: name(name), hp(hp), dmg(dmg), ap(ap), exp(exp), lvl(lvl) {}

std::string Mob::getName() const {
    return this->name;
}

bool Mob::isAlive() const{
  return (this->hp > 0);
}

void Mob::attack(Mob &target) {
    int dmg = this->dmg-(target.ap*2);
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
  std::cout << "Name: \033[1;31m" << this->name << "\033[0m \tLvl: \033[1;31m"<< this->lvl<<"\033[0m \n" << "HP: \033[1;32m" << this->hp << "\033[0m \n" << "Damage: \033[1;33m" << this->dmg << "\033[0m.\n" << "Armor: " << this->ap << std::endl;
}
void Mob::lvlUp() {
  this->lvl++;
  this->hp += 10;
  this->dmg += 5;
  this->ap += 2;
  this->exp = 0;
  std::cout << "\033[1;33m" << this->name << " has leveled up to level " << this->lvl << "!\033[0m. \n" << std::endl;
}