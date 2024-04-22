//
// Created by habetka on 9.6.19.
//
#include "Field.hpp"

Field::Field(int x, int y, const std::string & name) : name(name) {
  setPosition(Point(x, y));
}

Field::Field(int x, int y) {
  setPosition(Point(x, y));
}

void Field::setPosition(const Point & position) {
  coords.x = position.x;
  coords.y = position.y;
}

Point Field::getPosition() const {
  return coords;
}