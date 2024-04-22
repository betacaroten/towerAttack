#include "ComputerPlayer.hpp"

ComputerPlayer::ComputerPlayer() : Player ("AI", false, 0) {}

ComputerPlayer::ComputerPlayer(bool playing, unsigned int score)
: Player("AI", playing, score) {}

std::shared_ptr<Player> ComputerPlayer::clone() const {
  return std::make_shared<ComputerPlayer>(*this);
}
