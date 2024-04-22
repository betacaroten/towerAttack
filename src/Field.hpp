
#ifndef SEMES_FIELD_HPP
#define SEMES_FIELD_HPP

#include <ncurses.h>
#include <cmath>
#include <memory>
#include "Point.hpp"

class Field {
  public:
  Field() = default;
  Field(const std::string & name) : name(name) {};
  Field(int x, int y, const std::string & name);
  Field(int x, int y);
  
  virtual ~Field() {};
  virtual std::string save() const = 0;
  virtual void draw() const = 0;
  virtual std::shared_ptr<Field> clone() const = 0;
  
  virtual bool isPassable() const = 0;
  
  Point getPosition() const;
  void setPosition(const Point & position);
  
  protected:
  std::string name;
  Point coords;
};

#endif //SEMES_FIELD_HPP
