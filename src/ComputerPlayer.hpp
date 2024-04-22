#ifndef SEMES_COMPUTER_HPP
#define SEMES_COMPUTER_HPP

#include "Player.hpp"

class ComputerPlayer : public Player {
  public:
  
  ComputerPlayer();
  ComputerPlayer(bool playing, unsigned score);

  virtual std::shared_ptr<Player> clone() const override;

};

#endif //SEMES_COMPUTER_HPP
