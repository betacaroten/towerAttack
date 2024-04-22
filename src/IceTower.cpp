#include "IceTower.hpp"

IceTower::IceTower()
  : Tower("IceTower", 33, Range(3, 5), 1, 3) {}

void IceTower::drawChar() const {
  printw("i");
}

std::shared_ptr<Field> IceTower::clone() const {
  return std::make_shared<IceTower>(*this);
}