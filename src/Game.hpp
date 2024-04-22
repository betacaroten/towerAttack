#ifndef SEMES_GAME_HPP
#define SEMES_GAME_HPP

#include <ncurses.h>
#include <unistd.h>
#include <fstream>
#include <chrono>
#include <ncurses.h>

#include "Map.hpp"
#include "HumanPlayer.hpp"
#include "ComputerPlayer.hpp"
#include "Parser.hpp"

class Game {
  public:
  Game(std::ifstream &mapFile, bool fromSave);
  
  void endOfGame(int fileNumber);
  
  /**
   * Save actual state of game to save file
   * @param mapNumber - number of played map, used for creating save file name
   */
  void save(int mapNumber);
  
  void saveGame(int fileNumber);
  
  void parsePlayers(std::ifstream &savefile, int fileNumber);
  
  void move();
  
  /**
   * Choose entry position for player's army
   * @param mapFile - file of played map
   */
  void chooseStartingPosition(std::ifstream &mapFile);
  
  /**
   * Render actual state of game
   * @param firstPlayer - for illustrating player on move
   */
  void changeImage(bool firstPlayer);
  
  int compareScore();
  
  bool continueLoop();
  
  /**
   *  Main game loop
   * Can be interrupted by player early, game automatically saves
   * Game ends when one army is decimated or Raiders left battlefield
   * @param fileNumber
   */
  void startGame(int fileNumber);
  
  /**
   * For every member of army on move
   * control visibility of enemy's entities
   * Attack if can
   * @param firstPlayes
   */
  void controlRanges(bool firstPlayes);
  
  /**
   *
   * @return army of player on move
   */
  std::shared_ptr <Player> onTheMove();
  
  void parseRaiders(std::ifstream &raidersFile, int fileNumber);
  
  void changePlayer();
  
  private:
  
  Map map;
  Parser parser;
  std::pair <std::shared_ptr<Player>, std::shared_ptr<Player>> players;
  
  int timeOfMove = 5000;
  bool savedGame;
  
};

#endif //SEMES_GAME_HPP
