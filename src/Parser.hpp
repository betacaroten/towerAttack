#ifndef SEMES_PARSER_HPP
#define SEMES_PARSER_HPP

#include <fstream>
#include <sstream>
#include <cstring>
#include <memory>
#include <list>
#include <queue>
#include <map>
#include <cstdlib>

#include "Field.hpp"
#include "Pawn.hpp"
#include "IceTroll.hpp"
#include "MountainTroll.hpp"
#include "TorchMan.hpp"
#include "Archer.hpp"

#include "BasicTower.hpp"
#include "IceTower.hpp"
#include "FireTower.hpp"
#include "ShockTower.hpp"
#include "SniperTower.hpp"

class Parser {
  public:
  Parser() = default;
  
  /**
   * Parse player's army from save file
   * @param savefile
   * @param raiders
   */
  void parseSavedRaiders(std::ifstream &savefile, std::list<std::shared_ptr<Field>> &raiders);
  
  /**
   * Parse AI's army from save file
   * @param savefile
   * @param towers
   */
  void parseSavedTowers(std::ifstream &savefile, std::list<std::shared_ptr<Field>> &towers);
  
  /**
   * Parse definition of player's army
   * @param file - file with definition of Raiders
   * @param raiders - list of player's army
   */
  void parseRaiders(std::ifstream &file, std::list<std::shared_ptr<Field>> &raiders);

};

#endif //SEMES_PARSER_HPP
