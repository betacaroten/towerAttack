#ifndef SEMES_HUMANPLAYER_HPP
#define SEMES_HUMANPLAYER_HPP

#include "Player.hpp"

class HumanPlayer : public Player {
  public:
  HumanPlayer();
  HumanPlayer(bool playing, unsigned);
  
  virtual std::shared_ptr<Player> clone() const override;
};

#endif //SEMES_HUMANPLAYER_HPP
