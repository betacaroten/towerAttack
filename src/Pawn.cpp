#include "Pawn.hpp"

Pawn::Pawn()
  : Raider("Pawn", 18, Range(1, 2), 4, 1, 1) {}

std::shared_ptr<Field> Pawn::clone() const {
return std::make_shared<Pawn>(*this);
}

void Pawn::drawChar() const {
  printw("<");
}