#include "Archer.hpp"

Archer::Archer()
  : Raider("Archer", 20, Range(3, 5), 4, 30, 2) {}

void Archer::drawChar() const {
  printw("A");
}

std::shared_ptr<Field> Archer::clone() const {
  return std::make_shared<Archer>(*this);
}

