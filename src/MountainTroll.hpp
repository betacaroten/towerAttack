//
// Created by habetka on 3.6.19.
//

#ifndef SEMES_MOUNTAINTROLL_HPP
#define SEMES_MOUNTAINTROLL_HPP

#include "Raider.hpp"

class MountainTroll : public Raider {
  public:
  MountainTroll();
  
  virtual void drawChar() const override;
  
  std::shared_ptr<Field> clone() const override;
  
};

#endif //SEMES_MOUNTAINTROLL_HPP
