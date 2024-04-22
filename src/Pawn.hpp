#ifndef SEMES_PAWN_HPP
#define SEMES_PAWN_HPP

#include "Raider.hpp"

class Pawn : public Raider {
  public:
  Pawn();
  
  std::shared_ptr<Field> clone() const override;
  
  virtual void drawChar() const override;
};

#endif //SEMES_PAWN_HPP
