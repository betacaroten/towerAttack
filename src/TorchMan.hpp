#ifndef SEMES_TORCHMAN_HPP
#define SEMES_TORCHMAN_HPP

#include "Raider.hpp"
#include <ncurses.h>

class TorchMan : public Raider {
  public:
  TorchMan();
  
  virtual void drawChar() const override;
  
  std::shared_ptr<Field> clone() const override;

};

#endif //SEMES_TORCHMAN_HPP
