#include "Point.hpp"

Point::Point(int x, int y) : x(x), y(y) {}

Point::Point(const Point &point) {
  x = point.x;
  y = point.y;
}

Point& Point::operator=(const Point & point) {
  if (this == &point) {
    return *this;
  }
  x = point.x;
  y = point.y;
  return *this;
}

bool Point::operator==(const Point & point) const {
  if (point.x == x && point.y == y) {
    return true;
  }
  return false;
}

void Point::set(int i, int j) {
  x = i;
  y = j;
}

bool Point::operator!=(const Point & point) const {
  return !(point == *this);
}

bool Point::operator<(const Point a) const {
  if (x == a.x) {
    return y < a.y;
  }
  return x < a.x;
}
