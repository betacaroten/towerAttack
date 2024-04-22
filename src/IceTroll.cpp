#include "IceTroll.hpp"

IceTroll::IceTroll()
  : Raider("IceTroll", 26, Range(1, 3), 5, 3, 1) {}

void IceTroll::drawChar() const {
  printw("[");
}
std::shared_ptr<Field> IceTroll::clone() const {
  return std::make_shared<IceTroll>(*this);
}