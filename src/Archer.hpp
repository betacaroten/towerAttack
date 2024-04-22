#ifndef SEMES_ARCHER_HPP
#define SEMES_ARCHER_HPP

#include "Raider.hpp"

class Archer : public Raider {
  public:
  Archer();
  
  virtual void drawChar() const override;
  std::shared_ptr<Field> clone() const override;
  
};

#endif //SEMES_ARCHER_HPP
