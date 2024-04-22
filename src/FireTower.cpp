#include "FireTower.hpp"

  FireTower::FireTower()
  : Tower("FireTower", 12, Range(1, 4), 4, 1) {}
  
void FireTower::drawChar() const {
    printw("@");
  }
  
  std::shared_ptr<Field> FireTower::clone() const {
    return std::make_shared<FireTower>(*this);
  }
