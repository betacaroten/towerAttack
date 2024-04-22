#ifndef SEMES_ICETOWER_HPP
#define SEMES_ICETOWER_HPP

#include "Tower.hpp"

class IceTower : public Tower {
  public:
  IceTower();
  
  virtual void drawChar() const override;
  
  std::shared_ptr<Field> clone() const;
  
};

#endif //SEMES_ICETOWER_HPP
