#include "Screen.hpp"

void Screen::startNewGame(std::string mapName, int fileNumber) {
  std::ifstream mapFile(mapName.c_str());
  Game game(mapFile, 0);
  clear();
  std::string manual = "Choose entry for your army (from '#'):\n\n";
  printw(manual.c_str());
  refresh();
  game.chooseStartingPosition(mapFile);
  
  mapFile.close();
  
  std::string raidersFileName = "./examples/raiders/raiders" + std::to_string(fileNumber) + ".txt";
  std::ifstream raidersFile((raidersFileName).c_str());
  if (raidersFile.fail()) {
    attron(COLOR_PAIR(3));
    printw("File %s cannot be opened.\n", raidersFileName.c_str());
    attron(COLOR_PAIR(3));
    refresh();
  } else {
    system(("vim " + raidersFileName).c_str());
    system("sleep 0.1");
    game.parseRaiders(raidersFile, fileNumber);
    raidersFile.close();
    
    playAgainScreen();
    refresh();
    
  }
}

bool Screen::loadGame() {
  clear();
  attroff(COLOR_PAIR(8));
  std::string chose = "Chose from saved games: \n";
  std::string error = "Save file cannot be opened.\n"
                      "Chose another one.\n";
  printw(chose.c_str());
  attroff(COLOR_PAIR(8));
  refresh();
  
  std::string savedFiles = "0) save0.txt\n"
                           "1) save1.txt\n"
                           "\n"
                           "q) Quit\n";
  printw(savedFiles.c_str());
  refresh();
  attron(COLOR_PAIR(8));
  attroff(COLOR_PAIR(8));
  
  std::string savename;
  std::string saveFilename;
  
  int ch;
  bool chosen = false;
  while (!chosen) {
    ch = getchar();
    switch (ch) {
      case 'q':
        attron(COLOR_PAIR(8));
        printw("quit\n");
        attroff(COLOR_PAIR(8));
        refresh();
        chosen = true;
        break;
      case '0':
        savename = "save0.txt";
        chosen = true;
        break;
      case '1':
        savename = "save1.txt";
        chosen = true;
        break;
      default:
        attron(COLOR_PAIR(3));
        printw("Invalid choice.\nChoose again.\n");
        attroff(COLOR_PAIR(3));
        refresh();
        break;
    }
    
    saveFilename = "./examples/savedGames/" + savename;
    if (ch == 'q') {
      return true;
    }
    
    std::ifstream saveFile(saveFilename.c_str());
    if (saveFile.fail()) {
      attron(COLOR_PAIR(3));
      printw(error.c_str());
      attroff(COLOR_PAIR(3));
      
      refresh();
    } else {
      std::string fileNumberString = savename.substr(4);
      int fileNumber = std::atoi(fileNumberString.c_str());
      
      Game savedGame(saveFile, 1);
      
      savedGame.parsePlayers(saveFile, fileNumber);
      savedGame.save(fileNumber);
      saveFile.close();
      break;
    }
  }
  refresh();
  clear();
  
  playAgainScreen();
  
  return false;
}

bool Screen::chooseMap() {
  clear();
  attron(COLOR_PAIR(8));
  std::string chose = "Choose map:\n"
                      "0) map (8x8)\n"
                      "1) map (12x16)\n"
                      "\n"
                      "q) Quit\n";
  printw(chose.c_str());
  attroff(COLOR_PAIR(8));
  
  refresh();
  
  int ch;
  bool chosen = false;
  int mapNumber;
  
  std::string mapFile = "./examples/maps/map";
  while (!chosen) {
    ch = getch();
    switch (ch) {
      case 'q':
        mapFile = "quit";
        chosen = true;
        break;
      case '0':
        chosen = true;
        mapNumber = 0;
        mapFile += "0.txt";
        break;
      case '1':
        chosen = true;
        mapNumber = 1;
        mapFile += "1.txt";
        break;
      case -1:
        break;
      default:
        printw("%s", chose.c_str());
        printw("__%c\n", ch);
        attron(COLOR_PAIR(3));
        printw("Invalid option\nTry again.");
        attroff(COLOR_PAIR(3));
        refresh();
        
        break;
    }
  }
  if (ch == 'q') {
    return true;
  }
  
  startNewGame(mapFile, mapNumber);
  return false;
}


bool Screen::choseGameScreen() {
  attron(COLOR_PAIR(8));
  std::string chose = "Choose option:\n"
                      "0) "
                      "New Game\n"
                      "1) Load Game\n"
                      "\n"
                      "q) Quit\n";
  printw("%s", chose.c_str());
  attroff(COLOR_PAIR(8));
  refresh();
  
  bool chosen = false;
  int ch;
  int option;
  while (!chosen) {
    ch = getch();
    
    switch (ch) {
      case 'q':
        chosen = true;
        refresh();
        clear();
        break;
      case '0':
        printw("New Game\n");
        refresh();
        option = 0;
        chosen = true;
        break;
      case '1':
        printw("Load Game\n");
        refresh();
        option = 1;
        chosen = true;
        break;
      case -1:
        break;
      default:
        clear();
        printw("%s", chose.c_str());
        printw("   %c\n", ch);
        attron(COLOR_PAIR(3));
        printw("Invalid option\n"
               "Try again.\n");
        attroff(COLOR_PAIR(3));
        
        refresh();
        break;
    }
  }
  
  if (ch == 'q') {
    return true;
  }
  
  if (option == 0) {
    bool mapQuit = chooseMap();
    if (mapQuit) {
      if (choseGameScreen()) {
        return true;
      } else {
        return false;
      }
    }
  } else {
    bool saveFileQuit = loadGame();
    if (saveFileQuit) {
      return choseGameScreen();
    }
  }
  return true;
}

bool Screen::playAgainScreen() {
  attron(COLOR_PAIR(2));
  printw("\n\nPlay again? (y/n)\n");
  attroff(COLOR_PAIR(2));
  refresh();
  int ch;
  int option;
  bool chosen = false;
  while (!chosen) {
    ch = getch();
    switch (ch) {
      case 'y':
      case 'Y':
        chosen = true;
        option = 1;
        break;
      case 'n':
      case 'N':
      case 'q':
        chosen = true;
        option = 0;
        break;
      case -1:
        break;
      default:
        printw("  %c\n", ch);
        clear();
        attron(COLOR_PAIR(3));
        printw("Invalid option\n"
               "Try again.\n");
        attroff(COLOR_PAIR(3));
        
        refresh();
        break;
    }
  }
  
  if (!option) {
    return true;
  }
  return choseGameScreen();
}

