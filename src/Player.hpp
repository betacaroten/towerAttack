#ifndef SEMES_PLAYER_HPP
#define SEMES_PLAYER_HPP

#include <memory>
#include <sstream>
#include <list>
#include "Field.hpp"
#include "Entity.hpp"

class Player {
  public:
  
  Player() = default;
  
  Player(std::string name, bool playing, unsigned scored);
  
  std::string save();
  
  void scored();
  
  unsigned getScore();
  
  void reset();
  
  void offTheMap(std::shared_ptr <Field> &raider);
  
  bool onTheMove() const;
  
  void changePlayer();
  
  bool isAlive();
  
  void printScore();
  
  std::list <std::shared_ptr<Field>> army;
  
  protected:
  
  virtual ~Player() = default;
  
  virtual std::shared_ptr <Player> clone() const = 0;
  
  std::string name;
  bool playing;
  unsigned score;
  
};

#endif //SEMES_PLAYER_HPP
