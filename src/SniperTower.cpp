#include "SniperTower.hpp"

SniperTower::SniperTower()
  : Tower("SniperTower", 10, Range(1, 3), 8, 5) {}

void SniperTower::drawChar() const {
  printw("P");
}

