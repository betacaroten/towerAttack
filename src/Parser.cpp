#include "Parser.hpp"

void Parser::parseSavedRaiders(std::ifstream &savefile, std::list<std::shared_ptr<Field>> &raiders) {
  std::string line;
  std::string type;
  int x, y;
  int hp, coolingTime;
  while (line != "end") {
    getline(savefile, line);
    std::istringstream iss(line);
    iss >> type >> x >> y >> hp >> coolingTime;
    
    if (type == "Pawn") {
      Pawn raider;
      raider.setPosition(Point(x, y));
      auto r = raider.clone();
      auto downcastedPtr = std::dynamic_pointer_cast<Entity>(r);
      downcastedPtr->setSaved(hp, coolingTime);
      raiders.push_back(r);
      
    } else if (type == "Archer") {
      Archer raider;
      raider.setPosition(Point(x, y));
      auto r = raider.clone();
      auto downcastedPtr = std::dynamic_pointer_cast<Entity>(r);
      downcastedPtr->setSaved(hp, coolingTime);
      raiders.push_back(r);
      
    } else if (type == "IceTroll") {
      IceTroll raider;
      raider.setPosition(Point(x, y));
      auto r = raider.clone();
      auto downcastedPtr = std::dynamic_pointer_cast<Entity>(r);
      downcastedPtr->setSaved(hp, coolingTime);
      raiders.push_back(r);
      
    } else if (type == "MountainTroll") {
      MountainTroll raider;
      raider.setPosition(Point(x, y));
      auto r = raider.clone();
      auto downcastedPtr = std::dynamic_pointer_cast<Entity>(r);
      downcastedPtr->setSaved(hp, coolingTime);
      raiders.push_back(r);
      
    } else if (type == "TorchMan") {
      TorchMan raider;
      raider.setPosition(Point(x, y));
      auto r = raider.clone();
      auto downcastedPtr = std::dynamic_pointer_cast<Entity>(r);
      downcastedPtr->setSaved(hp, coolingTime);
      raiders.push_back(r);
    }
  }
}


void Parser::parseSavedTowers(std::ifstream &savefile, std::list<std::shared_ptr<Field>> &towers) {
  std::string line;
  std::string type;
  int x, y;
  int hp, coolingTime;
  while (line != "end") {
    getline(savefile, line);
    std::istringstream iss(line);
    iss >> type >> x >> y >> hp >> coolingTime;
    if (type == "SniperTower") {
      SniperTower tower;
      tower.setPosition(Point(x, y));
      auto t = tower.clone();
      auto downcastedPtr = std::dynamic_pointer_cast<Entity>(t);
      downcastedPtr->setSaved(hp, coolingTime);
      towers.push_back(t);
      
    } else if (type == "ShockTower") {
      ShockTower tower;
      tower.setPosition(Point(x, y));
      auto t = tower.clone();
      auto downcastedPtr = std::dynamic_pointer_cast<Entity>(t);
      downcastedPtr->setSaved(hp, coolingTime);
      towers.push_back(t);
      
    } else if (type == "BasicTower") {
      BasicTower tower;
      tower.setPosition(Point(x, y));
      auto t = tower.clone();
      auto downcastedPtr = std::dynamic_pointer_cast<Entity>(t);
      downcastedPtr->setSaved(hp, coolingTime);
      towers.push_back(t);
      
    } else if (type == "IceTower") {
      IceTower tower;
      tower.setPosition(Point(x, y));
      auto t = tower.clone();
      auto downcastedPtr = std::dynamic_pointer_cast<Entity>(t);
      downcastedPtr->setSaved(hp, coolingTime);
      towers.push_back(t);
      
    } else if (type == "FireTower") {
      FireTower tower;
      tower.setPosition(Point(x, y));
      auto t = tower.clone();
      auto downcastedPtr = std::dynamic_pointer_cast<Entity>(t);
      downcastedPtr->setSaved(hp, coolingTime);
      towers.push_back(t);
    }
  }
}

void Parser::parseRaiders(std::ifstream &file, std::list<std::shared_ptr<Field>> &raiders) {
  std::string line;
  unsigned raiderNumber;
  std::string raiderType;
  while (std::getline(file, line)) {
    if (!isdigit(line[0])) {
      continue;
    }
    std::istringstream iss(line);
    iss >> raiderNumber >> raiderType;
    
    if (raiderType == "Pawn") {
      while (raiderNumber) {
        Pawn r;
        auto raider = r.clone();
        raiders.push_back(raider);
        raiderNumber--;
      }
    } else if (raiderType == "Archer") {
      while (raiderNumber) {
        Archer r;
        auto raider = r.clone();
        raiders.push_back(raider);
        raiderNumber--;
      }
    } else if (raiderType == "Mountain_Troll") {
      while (raiderNumber) {
        MountainTroll r;
        auto raider = r.clone();
        raiders.push_back(raider);
        raiderNumber--;
      }
    } else if (raiderType == "Ice_Troll") {
      while (raiderNumber) {
        IceTroll r;
        auto raider = r.clone();
        raiders.push_back(raider);
        raiderNumber--;
      }
    } else if (raiderType == "Torchman") {
      while (raiderNumber) {
        TorchMan r;
        auto raider = r.clone();
        raiders.push_back(raider);
        raiderNumber--;
      }
    }
  }
}
