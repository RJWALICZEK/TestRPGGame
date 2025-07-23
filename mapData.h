#pragma once
#include <vector>
#include <string>
#include <string>

struct MapInfo {
  std::string name;
  std::string label;
  std::vector<std::vector<char>> grid;
};

 /*Graveyard_Ruins;
 Darkwood;
 Stoneruin;
Oldquarry;
Grimvalley5;
 Fallentower;
Wastedfield;
Lostcamp;
Ravenscar;
Wolfden;
Stonehill;
 Bloodgate;
Duskport;*/

extern std::vector<MapInfo> gameMaps;