#include "ShockTower.hpp"

ShockTower::ShockTower()
  : Tower("ShockTower", 20, Range(3, 8), 7, 5) {}

void ShockTower::drawChar() const {
  printw("S");
}
