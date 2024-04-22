#ifndef SEMES_TOWER_HPP
#define SEMES_TOWER_HPP

#include "Entity.hpp"

class Tower : public Entity {
  public:
  Tower() = default;
  Tower (const std::string & name,
         int hp,
         const Range &range,
         unsigned attackPower,
         unsigned cooldownTime);
  
  ~Tower() = default;
  
  virtual void draw() const override {
    if (hit) {
      attron(COLOR_PAIR(3));
      drawChar();
      attroff(COLOR_PAIR(3));
    } else if (firing) {
      attron(COLOR_PAIR(1));
      drawChar();
      attroff(COLOR_PAIR(1));
    } else {
      attron(COLOR_PAIR(5));
      drawChar();
      attroff(COLOR_PAIR(5));
    }
  }
  
  
};

#endif //SEMES_TOWER_HPP
