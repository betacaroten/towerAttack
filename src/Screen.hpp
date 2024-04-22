#ifndef SEMES_SCREEN_HPP
#define SEMES_SCREEN_HPP

#include <string>

#include "Game.hpp"

class Screen {
  public:
  Screen() = default;
  
  /**
   * Screen offers to player to specify entry point of their army
   * and to define numbers of their Raiders
   * @param mapName - name of map file chosen by player
   * @param fileNumber - value chosen in previous screen by player
   */
  void startNewGame(std::string mapName, int fileNumber);
  
  /**
   * Screen shows menu with available save files,
   * player can choose to play some, or to return to previous state
   * @return true if player wants to quit the game, bubbles through to main
   */
  bool loadGame();
  
  /**
   * Screen shows menu of available maps,
   * player chooses serial number of map, or can quit ro previous state
   * @return true if player wants to quit the game, bubbles through to main
   */
  bool chooseMap();
  
  /**
   * Screen shows menu of activities
   * User can start playing new game from map by their choice,
   * load saved game,
   * or quit the game entirely
   * @return true if player wants to quit the game, returns to main and terminate the game
   */
  bool choseGameScreen();
  
  /**
   * Screen shows after at least one game is played,
   * player can choose to terminate the game, or to play another map
   * @return true if player wants to quit the game, bubbles through to main
   */
  bool playAgainScreen();

};

#endif //SEMES_SCREEN_HPP
