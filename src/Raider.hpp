#ifndef SEMES_RAIDER_HPP
#define SEMES_RAIDER_HPP

#include "Entity.hpp"

class Raider : public Entity {
  public:
  Raider() = default;
  
  Raider(const std::string &name,
         int hp,
         const Range &range,
         unsigned attackPower,
         unsigned cooldownTime,
         int speed);
  
  ~Raider() = default;
  
  void nullCounter();
  void resetMoveCounter();
  bool moveToNextField();
  virtual void draw() const override;
  protected:
  
  unsigned movesNeededForReachingNextField;
  int movesToNextField;
  int movementSpeed;
  
};

#endif //SEMES_RAIDER_HPP
