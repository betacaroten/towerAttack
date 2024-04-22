#include <sstream>
#include "Blank.hpp"

Blank::Blank(int x, int y)
  : Field(x, y, "blank") {}

std::string Blank::save() const {
  std::ostringstream oss;
  oss << name << " " << getPosition().x << " " << getPosition().y << "\n";
  return oss.str();
}

void Blank::draw() const {
  printw(" ");
}

std::shared_ptr<Field> Blank::clone() const {
  return std::make_shared<Blank>(*this);
}

bool Blank::isPassable() const {
  return true;
}