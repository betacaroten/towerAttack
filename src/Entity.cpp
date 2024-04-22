#include <sstream>
#include "Entity.hpp"
#include "Range.hpp"

Entity::Entity(const std::string &name,
               int hp,
               const Range &range,
               unsigned attackPower,
               unsigned cooldownTime)
  : Field(name),
    hp(hp),
    range(range),
    attackPower(attackPower),
    cooldownTime(cooldownTime) {
  coolingTime = cooldownTime;
  hit = false;
  firing = false;
  alive = isAlive();
}

bool Entity::isPassable() const {
  return false;
}

void Entity::setSaved(int newhp, int cool) {
  hp = newhp;
  coolingTime = cool;
}

int Entity::gethp() {
  return hp;
}

std::string Entity::save() const {
  std::ostringstream oss;
  oss << name << " " << coords.x << " "
  << coords.y << " " << hp << " "
  << coolingTime << "\n";
  return oss.str();
}

bool Entity::isAlive() {
  if (hp > 0) {
    alive = true;
  } else {
    alive = false;
  }
  return alive;
}

bool Entity::isAlive(std::shared_ptr<Entity> &entity) {
  if (entity->gethp() > 0) {
    return true;
  }
  return false;
}

bool Entity::isCooling() {
  return coolingTime > 0;
}

bool Entity::isPointInRange(std::shared_ptr<Field> &controlledPosition) const {
  return pow(controlledPosition->getPosition().x - coords.x, 2)
         + pow(controlledPosition->getPosition().y - coords.y, 2) <= range.max * range.max
         && pow(controlledPosition->getPosition().x - coords.x, 2)
         + pow(controlledPosition->getPosition().y - coords.y, 2) >= range.min * range.min;
}

void Entity::cool() {
  coolingTime--;
}

void Entity::resetCoolingTime() {
  coolingTime = cooldownTime;
}

void Entity::takeDamage(unsigned damage) {
  hp -= damage;
  hit = true;
  firing = false;
  if (hp <= 0) {
    alive = false;
  }
}

void Entity::reset() {
  firing = false;
  hit = false;
}

void Entity::damageEnemy(std::shared_ptr<Entity> &enemy) {
  if (isAlive(enemy)) {
    enemy->takeDamage(attackPower);
  }
  resetCoolingTime();
}

bool Entity::attack(std::shared_ptr<Entity> &enemy) {
  if (!isCooling() && !hit) {
    damageEnemy(enemy);
    firing = true;
    return true;
  }
  firing = false;
  return false;
}
