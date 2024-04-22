#ifndef SEMES_ICETROLL_HPP
#define SEMES_ICETROLL_HPP

#include "Raider.hpp"

class IceTroll : public Raider {
  public:
  IceTroll();
  
  virtual void drawChar() const override;
  std::shared_ptr<Field> clone() const override;
  
};

#endif //SEMES_ICETROLL_HPP
