#ifndef SEMES_SHOCKTOWER_HPP
#define SEMES_SHOCKTOWER_HPP

#include "Tower.hpp"

class ShockTower : public Tower {
  public:
  ShockTower();
  
  virtual void drawChar() const override;
  
  std::shared_ptr<Field> clone() const override {
    return std::make_shared<ShockTower>(*this);
  }
  
};


#endif //SEMES_SHOCKTOWER_HPP
