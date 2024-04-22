#include "BasicTower.hpp"

BasicTower::BasicTower()
  : Tower("BasicTower", 25, Range(2, 5), 5, 10) {}

void BasicTower::drawChar() const {
  printw("I");
}

std::shared_ptr<Field> BasicTower::clone() const {
  return std::make_shared<BasicTower>(*this);
}