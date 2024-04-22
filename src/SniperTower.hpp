#ifndef SEMES_SNIPERTOWER_HPP
#define SEMES_SNIPERTOWER_HPP

#include "Tower.hpp"

class SniperTower : public Tower {
  public:
  SniperTower();
  
  virtual void drawChar() const override;
  
  std::shared_ptr<Field> clone() const override {
    return std::make_shared<SniperTower>(*this);
  }

};

#endif //SEMES_SNIPERTOWER_HPP
