#include "Game.hpp"

Game::Game(std::ifstream &mapFile, bool fromSave) {
  savedGame = fromSave;
  
  if (savedGame) {
    map.parseSaveMap(mapFile);
    
  } else {
    HumanPlayer human;
    players.first = human.clone();
    ComputerPlayer computer;
    players.second = computer.clone();
  }
}

void Game::parsePlayers(std::ifstream &savefile, int fileNumber) {
  std::string line;
  clear();
  std::istringstream iss(line);
  std::string name;
  int playing;
  unsigned score;
  iss >> name >> playing >> score;
  HumanPlayer human(playing, score);
  players.first = human.clone();
  parser.parseSavedRaiders(savefile, players.first->army);
  
  getline(savefile, line);
  std::istringstream iiss(line);
  iiss >> name >> playing >> score;
  ComputerPlayer computer(playing, score);
  players.second = computer.clone();
  parser.parseSavedTowers(savefile, players.second->army);
  
  map.fillWithArmies(players.first->army, players.second->army);
  
  startGame(fileNumber);
}

void Game::chooseStartingPosition(std::ifstream &mapFile) {
  map.fillBlankMap(mapFile, players.second->army);
  bool validStart = false;
  char i, j;
  map.drawIndexed();
  
  while (!validStart) {
    std::cin >> i >> j;
    printw("[%d, %d]\n", i - 'a', j - 'a');
    refresh();
    bool wall = false;
    if (map.validStart(i - 'a', j - 'a', &wall)) {
      map.setStart(i - 'a', j - 'a');
      refresh();
      validStart = true;
    } else {
      printw("Invalid starting position.\n"
             "Choose another one.\n");
      refresh();
    }
  }
  Point start(i - 'a', j - 'a');
  map.setStartPosition(start);
  std::list <Point> route = map.findRoute(start);
  map.parseTowers(mapFile, route, players.second->army);
  
  clear();
}

void Game::save(int mapNumber) {
  
  std::string saveFileName = "./examples/savedGames/save" + std::to_string(mapNumber) + ".txt";
  std::ofstream saveFile(saveFileName);
  if (saveFile.fail()) {
    printw("Save file error.\n");
  } else {
    std::stringstream oss;
    oss << map.save();
    std::string savedMap = oss.str();
    saveFile << savedMap
             << players.first->save() << "\n"
             << players.second->save();
    
    saveFile.close();
  }
}

int Game::compareScore() {
  if (players.first->getScore() == players.second->getScore()) {
    return 0;
  } else if (players.first->getScore() < players.second->getScore()) {
    return 2;
  }
  return 1;
}

void Game::changeImage(bool firstPlayer) {
  clear();
  attron(COLOR_PAIR(8));
  
  std::string hint = "  Towers:          Raiders:      \n"
                     "I Basic Tower  | < Pawn          \n"
                     "i Ice Tower    | [ Ice Troll     \n"
                     "P Sniper Tower | A Archer        \n"
                     "S Shock Tower  | M Mountain Troll\n"
                     "@ Fire Tower   | T Torchman      \n";
  
  printw("q) Quit (Game automatically saves)\n");
  printw("\n----------\n");
  attroff(COLOR_PAIR(8));
  
  map.draw();
  
  attron(COLOR_PAIR(8));
  printw("score:\n");
  attron(COLOR_PAIR(6));
  players.first->printScore();
  if (firstPlayer) {
    printw(".");
  }
  attroff(COLOR_PAIR(6));
  printw("\n");
  attron(COLOR_PAIR(5));
  players.second->printScore();
  if (!firstPlayer) {
    printw(".");
  }
  attroff(COLOR_PAIR(5));
  
  attron(COLOR_PAIR(8));
  printw("\n\nhint:\n%s\n", hint.c_str());
  attroff(COLOR_PAIR(8));
  refresh();
  
}

void Game::saveGame(int fileNumber) {
  save(fileNumber);
  attroff(COLOR_PAIR(9));
  printw("Your game was automatically saved.\n");
  attroff(COLOR_PAIR(9));
  refresh();
  system("sleep 1");
}

void Game::endOfGame(int fileNumber) {
  clear();
  int winner = compareScore();
  switch (winner) {
    case 1:
      attron(COLOR_PAIR(1));
      printw("YOU WIN\n");
      attroff(COLOR_PAIR(1));
      refresh();
      break;
    case 2:
      attron(COLOR_PAIR(3));
      printw("YOU LOSE\n");
      attroff(COLOR_PAIR(3));
      refresh();
      break;
    case 3:
      attron(COLOR_PAIR(2));
      printw("IT'S A DRAW\n");
      attroff(COLOR_PAIR(2));
      refresh();
      break;
    default:
      break;
  }
  saveGame(fileNumber);
}

bool Game::continueLoop() {
  if (!onTheMove()->isAlive()) {
    return false;
  }
  auto armyOnMove = onTheMove()->army;
  for (auto &i: armyOnMove) {
    if (i->getPosition() != Point(-2,-2)) {
      return true;
    }
  }
  return false;
}

void Game::move() {
  auto armyOnMove = players.first->army;
  
  for (auto &raiderOnMap: armyOnMove) {
    Point oldPosition = raiderOnMap->getPosition();
    if (oldPosition == Point(-2, -2)) { // dead or savely back home
      continue;
    }
    
    if (map.wentOffTheMap(oldPosition)) {
      map.hideTheDead(raiderOnMap);
      onTheMove()->scored();
      continue;
    }
    
    auto downcastedPtr = std::dynamic_pointer_cast<Raider>(raiderOnMap);
    if (!downcastedPtr->isAlive()) {
      continue;
    }
    
    Point start = oldPosition;
    if (downcastedPtr->moveToNextField()) {
      
      auto route = map.findRoute(start);
      if (route.empty()) {
        continue;
      }
      
      if (oldPosition != Point(-1, -1)) {
        route.pop_front();
      }
      
      auto nextField = route.front();
      if (map.validPosition(nextField) && map.fieldIsPassable(nextField)) {
        map.insert(raiderOnMap, nextField);
      }

    }
  }
}

void Game::startGame(int fileNumber) {
  int ch;
  nodelay(stdscr, TRUE);
  while (true) {
    if ((ch = getch()) == ERR) {
      clear();
  
      bool loop = continueLoop();
      if (!loop) {
        endOfGame(fileNumber);
        return;
      }
      players.first->reset();
      players.second->reset();
  
      auto armyOnMove = onTheMove()->army;
      bool firstPlayes = (players.first->army == armyOnMove);
      
      auto startOfMove = std::chrono::steady_clock::now();
      
      if (firstPlayes) {
        move();
      }
      
      controlRanges(firstPlayes);
      
      changeImage(firstPlayes);
      refresh();
      
      auto endOfMove = std::chrono::steady_clock::now();
      auto durationOfMove = std::chrono::duration_cast<std::chrono::microseconds>(endOfMove - startOfMove).count();
      
      if (durationOfMove < timeOfMove) {
        double sleepTime = (timeOfMove - durationOfMove) * 10e-5;
        std::ostringstream oss;
        oss << sleepTime;
        std::string str = oss.str();
        system(("sleep " + str).c_str());
      }
      
      changePlayer();
      
      
    } else {
      if (ch == 'q') {
        saveGame(fileNumber);
        return;
      }
    }
  }
}

void Game::controlRanges(bool firstPlayes) {
  auto &center = players.first->army;
  auto &test = players.second->army;
  if (!firstPlayes) {
    test.swap(center);
  }
  
  for (auto &c: center) {
    Point centerPosition = c->getPosition();
    if (!map.validPosition(centerPosition.x, centerPosition.y)) {
      continue;
    }
    auto attacker = std::dynamic_pointer_cast<Entity>(c);
    if (!attacker->isAlive()) {
      continue;
    }
    
    for (auto &t: test) {
      Point testPosition = t->getPosition();
      if (!map.validPosition(testPosition.x, testPosition.y)) {
        continue;
      }
      
      auto target = std::dynamic_pointer_cast<Entity>(t);
      if (!target->isAlive()) {
        continue;
      }
      
      bool inRange = attacker->isPointInRange(t);
      
      if (inRange) {
        if (!attacker->attack(target)) {
          attacker->cool();
        } else if (!target->isAlive()) {
          map.hideTheDead(t);
          onTheMove()->scored();
        }
      }
    }
  }
  
  if (!firstPlayes) {
    test.swap(center);
  }
}

std::shared_ptr <Player> Game::onTheMove() {
  if (players.first->onTheMove()) {
    return players.first;
  } else {
    return players.second;
  }
}

void Game::parseRaiders(std::ifstream &raidersFile, int fileNumber) {
  parser.parseRaiders(raidersFile, players.first->army);
  
  startGame(fileNumber);
}

void Game::changePlayer() {
  
  players.first->changePlayer();
  players.second->changePlayer();
}
  