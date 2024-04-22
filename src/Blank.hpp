#ifndef SEMES_BLANK_HPP
#define SEMES_BLANK_HPP

#include "Field.hpp"

class Blank : public Field {
  public:
  Blank() = default;
  Blank(int x, int y);

  std::shared_ptr<Field> clone() const override;
  
  virtual std::string save() const override;
  void draw() const override;
  
  bool isPassable() const override;
};

#endif //SEMES_BLANK_HPP
