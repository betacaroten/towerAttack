#include "MountainTroll.hpp"

MountainTroll::MountainTroll()
  : Raider("MountainTroll", 45, Range(1, 4), 6, 5, 5) {}

void MountainTroll::drawChar() const {
  printw("M");
}

std::shared_ptr<Field> MountainTroll::clone() const {
  return std::make_shared<MountainTroll>(*this);
}
