#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <termios.h>
#include <unistd.h>

inline void sleep(int ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

inline char getChar() {
    char buf = 0;
    termios old{};
    tcgetattr(STDIN_FILENO, &old);             // pobierz aktualne ustawienia terminala
    termios newt = old;
    newt.c_lflag &= ~(ICANON | ECHO);          // wyłącz oczekiwanie na enter i echo znaków
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // ustaw nowe tryby
    ssize_t ret = read(STDIN_FILENO, &buf, 1); // wczytaj jeden znak
    (void)ret;  // jawne zignorowanie wartości, by uniknąć warningu
    tcsetattr(STDIN_FILENO, TCSADRAIN, &old); // przywróć stare ustawienia
    return buf;
}
