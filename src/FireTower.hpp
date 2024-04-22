#ifndef SEMES_FIRETOWER_HPP
#define SEMES_FIRETOWER_HPP

#include "Tower.hpp"

class FireTower : public Tower {
  public:
  FireTower();
  
  std::shared_ptr<Field> clone() const override;
  
  virtual void drawChar() const override ;
  
};

#endif //SEMES_FIRETOWER_HPP
