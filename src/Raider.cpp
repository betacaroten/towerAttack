//
// Created by habetka on 9.6.19.
//

#include "Raider.hpp"

Raider::Raider(const std::string &name,
               int hp,
               const Range &range,
               unsigned attackPower,
               unsigned cooldownTime,
               int speed)
  : Entity(name, hp, range, attackPower, cooldownTime),
    movementSpeed(speed) {
  
  Point initPoint(-1, -1);
  setPosition(initPoint);
  nullCounter();
}

void Raider::draw() const {
  if (hit) {
    attron(COLOR_PAIR(3));
    drawChar();
    attroff(COLOR_PAIR(3));
  } else if (firing) {
    attron(COLOR_PAIR(1));
    drawChar();
    attroff(COLOR_PAIR(1));
  } else {
    attron(COLOR_PAIR(6));
    drawChar();
    attroff(COLOR_PAIR(6));
  }
}

void Raider::nullCounter() {
  movesNeededForReachingNextField = 2;
  movesToNextField = 0;
}

void Raider::resetMoveCounter() {
  movesToNextField = movesNeededForReachingNextField + movementSpeed;
}

bool Raider::moveToNextField() {
  movesToNextField--;
  if (movesToNextField <= 0) {
    resetMoveCounter();
    return true;
  }
  return false;
}
