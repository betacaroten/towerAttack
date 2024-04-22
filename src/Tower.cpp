#include "Tower.hpp"

Tower::Tower(const std::string &name,
             int hp,
             const Range &range,
             unsigned attackPower,
             unsigned cooldownTime)
  : Entity(name, hp, range, attackPower, cooldownTime) {}