#ifndef SEMES_BASICTOWER_HPP
#define SEMES_BASICTOWER_HPP

#include "Tower.hpp"

class BasicTower : public Tower {
  public:
  BasicTower();
  
  std::shared_ptr<Field> clone() const override;
  
  virtual void drawChar() const override;

};

#endif //SEMES_BASICTOWER_HPP
