#ifndef SEMES_POINT_HPP
#define SEMES_POINT_HPP

#include <iostream>
#include <ncurses.h>

struct Point {
  
  Point(int x, int y);
  Point(const Point &point);
  
  Point() {};
  
  ~Point() {};
  
  void set(int i, int j);
  
  Point& operator=(const Point & point);
  bool operator==(const Point & point) const;
  bool operator!=(const Point & point) const;
  bool operator<(const Point a) const;
  
  int x;
  int y;
  
};

#endif //SEMES_POINT_HPP
