#ifndef SEMES_ENTITY_HPP
#define SEMES_ENTITY_HPP

#include "Field.hpp"
#include "Range.hpp"

class Entity : public Field {
  public:
  Entity() = default;
  
  Entity(const std::string &name,
         int hp,
         const Range &range,
         unsigned attackPower,
         unsigned cooldownTime);
  
  ~Entity() = default;
  
  bool isAlive();
  
  /**
   * Control if enemy is alive
   * @param entity - enemy
   * @return
   */
  bool isAlive(std::shared_ptr<Entity> &entity);
  
  int gethp();
  
  /**
   * Control if attacker (ax, ay) reaches its enemy (ex, ey)
   * Compare radius of maximum range and minimum range of attacker's attack visibility
   * with distance from each other
   * Used formula:
   * (ex - ax)^2 + (ey - ay)^2 <= maximal_range && (ex - ax)^2 + (ey - ay)^2 >= minimal_range
   * @param controlledPosition
   * @return true - enemy lies in range of attacker, false - attacker doesn't reach its enemy
   */
  bool isPointInRange(std::shared_ptr<Field> &controlledPosition) const;

  /**
   * Function used when loading from save file
   * @param newhp
   * @param cool
   */
  void setSaved(int newhp, int cool);
  
  std::string save() const;
 
  virtual bool isPassable() const override;
  
  /**
   * Control if entity can attack
   * @return
   */
  bool isCooling();
  
  /**
   * Decrement cooling time of entity of player on move
   */
  void cool();
  void resetCoolingTime();
  void takeDamage(unsigned damage);
  
  void damageEnemy(std::shared_ptr<Entity> &enemy);
  
  /**
   * Attack on enemy if can - isn't cooling and enemy is alive
   * @param enemy
   * @return true - damaged enemy, false - didn't attack
   */
  bool attack(std::shared_ptr<Entity> &enemy);
  
  void reset();
  
  protected:
  
  virtual void drawChar() const = 0;
  bool hit;
  bool firing;
  bool alive;
  int hp;
  Range range;
  unsigned attackPower;
  unsigned cooldownTime;
  int coolingTime;
};
#endif //SEMES_ENTITY_HPP
