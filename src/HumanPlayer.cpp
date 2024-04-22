#include "HumanPlayer.hpp"

HumanPlayer::HumanPlayer() : Player(":)", true, 0) {}

HumanPlayer::HumanPlayer(bool playing, unsigned score)
  : Player(":)", playing, score) {}

std::shared_ptr<Player> HumanPlayer::clone() const {
  return std::make_shared<HumanPlayer>(*this);
}

