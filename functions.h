#pragma once
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <termios.h>
#include <thread>
#include <unistd.h>

inline void sleep(int ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

inline char getChar() {
  char buf = 0;
  termios old{};
  tcgetattr(STDIN_FILENO, &old); // pobierz aktualne ustawienia terminala
  termios newt = old;
  newt.c_lflag &= ~(ICANON | ECHO); // wyłącz oczekiwanie na enter i echo znaków
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);   // ustaw nowe tryby
  ssize_t ret = read(STDIN_FILENO, &buf, 1); // wczytaj jeden znak
  (void)ret; // jawne zignorowanie wartości, by uniknąć warningu
  tcsetattr(STDIN_FILENO, TCSADRAIN, &old); // przywróć stare ustawienia
  return buf;
}

inline void initRandom() { std::srand(std::time(nullptr)); }
inline int getRandomEnemyCount() {
  return std::rand() % 3 + 1; // 1,2,3
}
inline int getRandomStat() {
  return std::rand() % 4 + 1; // 1,2,3,4
}
inline int getRandomItem() {
  return std::rand() % 4 + 1; // 1,2,3,4
}

