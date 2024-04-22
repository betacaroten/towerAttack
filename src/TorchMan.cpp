#include "TorchMan.hpp"

  TorchMan::TorchMan()
  : Raider("TorchMan", 10, Range(1, 2), 2, 2, 1) {}
  
 void TorchMan::drawChar() const {
    printw("T");
  }
  
  std::shared_ptr<Field> TorchMan::clone() const {
    return std::make_shared<TorchMan>(*this);
  }

