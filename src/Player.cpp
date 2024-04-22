#include "Player.hpp"

Player::Player(std::string name, bool playing, unsigned scored)
: name(name), playing(playing), score(scored) {
  score = scored;
  reset();
}

std::string Player::save() {
  std::ostringstream oss;
  oss << name << " "
  << playing << " "
  << score << "\n";
  for (auto &a: army) {
    auto downcastedPtr = std::dynamic_pointer_cast<Entity>(a);
    oss << downcastedPtr->save();
  }
  oss << "end";
  return oss.str();
}

void Player::reset() {
  for (auto &a : army) {
    auto downcastedPtr = std::dynamic_pointer_cast<Entity>(a);
    downcastedPtr->reset();
  }
}

unsigned Player::getScore() {
  return score;
}

void Player::scored() {
  score++;
}

bool Player::onTheMove() const {
  return playing;
}

void Player::changePlayer() {
  playing = !playing;
}

void Player::printScore() {
  printw("%s %u", name.c_str(), score);
}

bool Player::isAlive() {
  for (auto &a: army) {
    auto downcastedPtr = std::dynamic_pointer_cast<Entity>(a);
    if (downcastedPtr->isAlive()) {
      return true;
    }
  }
  return false;
}
