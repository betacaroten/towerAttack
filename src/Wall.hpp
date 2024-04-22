#ifndef SEMES_WALL_HPP
#define SEMES_WALL_HPP

#include "Field.hpp"

class Wall : public Field {
  public:
  Wall(int x, int y);
  Wall(int x, int y, char type);
  
  virtual std::string save() const override;

  bool isPassable() const override;
  
  void draw() const override;
  char getType();
  
  std::shared_ptr<Field> clone() const override;
  
  private:
  char type;
  
};

#endif //SEMES_WALL_HPP
