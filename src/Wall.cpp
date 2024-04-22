#include <sstream>
#include "Wall.hpp"

Wall::Wall(int x, int y)
: Field(x, y, "wall"), type('#') {}

Wall::Wall(int x, int y, char type)
: Field(x, y, "xwall"), type(type) {}

std::string Wall::save() const {
  std::ostringstream oss;
  oss << name << " " << getPosition().x << " " << getPosition().y << " " << type << "\n";
  return oss.str();
}

void Wall::draw() const {
  attron(COLOR_PAIR(2));
  printw("#");
  attroff(COLOR_PAIR(2));
}

char Wall::getType() {
  return type;
}

std::shared_ptr<Field> Wall::clone() const {
return std::make_shared<Wall>(*this);
}

bool Wall::isPassable() const {
return false;
}