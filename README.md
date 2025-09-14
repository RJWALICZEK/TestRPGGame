# TestRPGGame

**TestRPGGame** is a small RPG-style game written in C++. The project was created to practice game mechanics, file structure, and modular programming.

---

## 🛠 Technology & Tools

- **Language:** C++  
- **Build System:** Makefile  
- **Main Components:**  
  - `main.cpp` – entry point of the game  
  - `game.cpp / game.h` – core game logic  
  - `map.cpp / map.h`, `gameMaps.h` – map handling  
  - `items.cpp / items.h` – item definitions and inventory logic  
  - `mob.cpp / mob.h` – enemy / character (mob) behaviors  
- **Other files:**  
  - `functions.h` – helper & utility functions  
  - `story.txt` – story text / narrative used in game  

---

## 🎮 Features

- Movement across game maps  
- Interaction with map elements (e.g. obstacles, items)  
- Basic combat and mob behaviors  
- Simple inventory / item system  
- Loading and managing game levels from map files  

---

## 🚀 How to Run / Build

1. Make sure you have a C++ compiler installed (e.g., `g++` or `clang++`).  
2. Clone this repository:  
   ```bash
   git clone https://github.com/RJWALICZEK/TestRPGGame.git
   cd TestRPGGame
