#ifndef SEMES_MAP_HPP
#define SEMES_MAP_HPP

#include <fstream>
#include <sstream>
#include <cstring>
#include <memory>
#include <list>
#include <queue>
#include <map>
#include <cstdlib>
#include <ncurses.h>

#include "Field.hpp"
#include "Wall.hpp"
#include "Blank.hpp"
#include "Point.hpp"
#include "Range.hpp"

#include "BasicTower.hpp"
#include "IceTower.hpp"
#include "FireTower.hpp"
#include "ShockTower.hpp"
#include "SniperTower.hpp"

class Map {
  public:
  Map() : height(0), width(0) {};
  
  ~Map() {};
  
  void initMap(std::ifstream &file);
  std::string save();
  void insert(std::shared_ptr<Field> &entity, const Point &newP);
  void draw();
  void drawIndexed();
  
  void setStartPosition(const Point &start);
  void fillBlankMap(std::ifstream &file, std::list<std::shared_ptr<Field>> &towers);
  
  void setStart(int x, int y);
  bool validStart(int x, int y, bool * wall);
  bool validPosition(int x, int y);
  bool validPosition(const Point &point);
  
  void parseTowers(std::ifstream &file, std::list<Point> &route, std::list<std::shared_ptr<Field>> &towers);
  bool parseSaveMap(std::ifstream &savefile);
  void fillWithArmies(std::list<std::shared_ptr<Field>> &raiders, std::list<std::shared_ptr<Field>> &towers);
  
  bool validElement(const std::string &element);
  bool wentOffTheMap(const Point &point);
  void hideTheDead(std::shared_ptr<Field> &entity);
  
  std::list<Point>::iterator nextMove(const Point &current, std::list<Point> &route);
  bool fieldIsPassable(const Point &field);
  std::list<Point> findRoute(Point &start);
  bool placeTower(std::list<Point> &route, std::shared_ptr<Field> &tower);

  std::list<Point> neighbouringFields(int x, int y);
  void initVisitedMap(std::map<Point, bool> &visited);
  
  std::list<Point> reconstructPath(const std::map<Point, Point> &prev, const Point &start);
  std::list<Point> reconstructPath(const std::map<Point, Point> &prev);
  std::list<Point> findRoute(const Point &start, const Point &hypotheticalPoint);
  
  private:
  int height, width;
  Point startPosition;
  Point endPosition;
  std::vector<std::vector<std::shared_ptr<Field>>> map;
};


#endif //SEMES_MAP_HPP
