#include "Map.hpp"

std::string Map::save() {
  std::stringstream oss;
  oss << "map\n"
      << height << " " << width << " "
      << startPosition.x << " " << startPosition.y << " "
      << endPosition.x << " " << endPosition.y << "\n";
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      oss << map[i][j]->save();
    }
  }
  oss << "end\n";
  return oss.str();
}

bool Map::validElement(const std::string &element) {
  return (element == "wall" || element == "blank" || element == "xwall");
}

void Map::fillWithArmies(std::list<std::shared_ptr<Field>> &raiders, std::list<std::shared_ptr<Field>> &towers) {
  for (auto &i: raiders) {
    Point position = i->getPosition();
    if (!validPosition(position)) {
      continue;
    }
    auto downcastedPtr = std::dynamic_pointer_cast<Entity>(i);
    if (!downcastedPtr->isAlive()) {
      Blank blank(position.x, position.y);
      map[position.x][position.y] = blank.clone();
      
    } else {
      map[position.x][position.y].reset();
      map[position.x][position.y] = i;
    }
  }
  for (auto &i: towers) {
    Point position = i->getPosition();
    if (!validPosition(position)) {
      continue;
    }
    auto downcastedPtr = std::dynamic_pointer_cast<Entity>(i);
    if (!downcastedPtr->isAlive()) {
      Blank blank(position.x, position.y);
      map[position.x][position.y] = blank.clone();
    } else {
      map[position.x][position.y].reset();
      map[position.x][position.y] = i;
    }
  }
}

bool Map::parseSaveMap(std::ifstream &savefile) {
  std::string line;
  getline(savefile, line);
  if (line != "map") {
    return false;
  }
  getline(savefile, line);
  std::istringstream iss(line);
  int x, y, sx, sy, ex, ey;
  iss >> x >> y >> sx >> sy >> ex >> ey;
  height = x;
  width = y;
  startPosition.set(sx, sy);
  endPosition.set(ex, ey);
  
  map.resize(height, std::vector<std::shared_ptr<Field >>(width));
  
  std::string element;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      getline(savefile, line);
      std::istringstream iiss(line);
      iiss >> element;
      if (validElement(element)) {
        if (element == "blank") {
          Blank blank(i, j);
          map[i][j] = blank.clone();
        } else if (element == "wall") {
          Wall wall(i, j);
          map[i][j] = wall.clone();
        } else if (element == "xwall") {
          Wall wall(i, j, 'X');
          map[i][j] = wall.clone();
        }
      } else {
        continue;
      }
    }
  }
  getline(savefile, line);
  return true;
}

std::list<Point>::iterator Map::nextMove(const Point &current, std::list<Point> &route) {
  for (auto i = route.begin(); i != route.end(); i++) {
    if (*i == current) {
      return std::next(i);
    }
  }
  return route.end();
}

bool Map::fieldIsPassable(const Point &field) {
  return map[field.x][field.y]->isPassable();
}

std::list<Point> Map::findRoute(Point &start) {
  if (!validPosition(start)) {
    start = startPosition;
  }
  std::list<Point> route;
  
  std::queue<Point> opened;
  std::map<Point, bool> visited;
  std::map<Point, Point> prev;
  initVisitedMap(visited);
  
  opened.push(start);
  if (start == endPosition) {
    route.push_front(start);
    return route;
  }
  
  while (!opened.empty()) {
    Point currentPosition = opened.front();
    opened.pop();
    visited[currentPosition] = true;
    
    std::list<Point> nextIndices = neighbouringFields(currentPosition.x, currentPosition.y);
    for (auto &neighbour : nextIndices) {
      
      if (neighbour == endPosition) {
        prev.insert(std::make_pair(neighbour, currentPosition));
        route = reconstructPath(prev, start);
        return route;
      }
      
      if (!visited[neighbour] && map[neighbour.x][neighbour.y]->isPassable()) {
        opened.push(neighbour);
        prev.insert(std::make_pair(neighbour, currentPosition));
        visited[neighbour] = true;
      }
    }
    
    visited[currentPosition] = true;
  }
  return route;
}

bool Map::wentOffTheMap(const Point &point) {
  return point == endPosition;
}

bool Map::placeTower(std::list<Point> &route, std::shared_ptr<Field> &tower) {
  int random;
  Point position = startPosition;
  Point current = startPosition;
  
  int maxTries = route.size();
  
  for (int i = 0; i < maxTries; i++) {
    random = rand() % route.size();
    for (int i = 1; i < random - 1; i++) {
      position = (*nextMove(current, route));
      current = position;
    }
    
    if (!(validPosition(position.x, position.y) && position != startPosition)) {
      continue;
    }
    
    auto newRoute = findRoute(startPosition, current);
    if (!newRoute.empty()) {
      tower->setPosition(current);
      map[current.x][current.y].reset();
      map[current.x][current.y] = tower;
      route = newRoute;
      return true;
      
    } else {
    }
  }
  return false;
}

void Map::hideTheDead(std::shared_ptr<Field> &entity) {
  Point crimeScene = entity->getPosition();
  Blank blank(crimeScene.x, crimeScene.y);
  map[crimeScene.x][crimeScene.y].reset();
  map[crimeScene.x][crimeScene.y] = blank.clone();
  entity->setPosition(Point(-2, -2));
}

void Map::insert(std::shared_ptr<Field> &entity, const Point &newP) {
  
    Point oldP = entity->getPosition();
    entity->setPosition(newP);
    
    map[newP.x][newP.y].reset();
    map[newP.x][newP.y] = entity;
    
    if (validPosition(oldP)) {
      map[oldP.x][oldP.y].reset();
      Blank blank(oldP.x, oldP.y);
      map[oldP.x][oldP.y] = blank.clone();
    }
  }

void Map::draw() {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      map[i][j]->draw();
    }
    printw("\n");
  }
}

void Map::drawIndexed() {
  printw("  ");
  for (int a = 0; a < width; a++) {
    printw("%c ", a + 'a');
  }
  printw("\n");
  for (int i = 0; i < height; i++) {
    printw("%c", i + 'a');
    for (int j = 0; j < width; j++) {
      printw("|");
      bool wall = false;
      if (!validStart(i, j, &wall)) {
        if (wall) {
          attron(COLOR_PAIR(2));
          printw("X");
          attroff(COLOR_PAIR(2));
          continue;
        }
      }
      map[i][j]->draw();
    }
    printw("\n");
  }
  refresh();
}

void Map::parseTowers(std::ifstream &file, std::list<Point> &route, std::list<std::shared_ptr<Field>> &towers) {
  
  std::string line;
  char towerType = 'a';
  unsigned towerNumber = 0;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    iss >> towerType >> towerNumber;
    
    if (towerType == 'B') {
      while (towerNumber) {
        BasicTower t;
        auto tower = t.clone();
        if (placeTower(route, tower)) {
          towers.push_front(tower);
        } else {
          towers.push_front(tower);
        }
        towerNumber--;
        
      }
    } else if (towerType == 'I') {
      while (towerNumber) {
        IceTower t;
        auto tower = t.clone();
        if (placeTower(route, tower)) {
          towers.push_front(tower);
        }
        towerNumber--;
      }
    } else if (towerType == 'F') {
      while (towerNumber) {
        FireTower t;
        auto tower = t.clone();
        if (placeTower(route, tower)) {
          towers.push_front(tower);
        }
        
        towerNumber--;
      }
    } else if (towerType == 'S') {
      while (towerNumber) {
        SniperTower t;
        auto tower = t.clone();
        if (placeTower(route, tower)) {
          towers.push_front(tower);
        }
        towerNumber--;
      }
    } else if (towerType == 'Z') {
      while (towerNumber) {
        ShockTower t;
        auto tower = t.clone();
        if (placeTower(route, tower)) {
          towers.push_front(tower);
        }
        
        towerNumber--;
      }
    }
  }
}

void Map::setStart(int x, int y) {
  Blank blank(x, y);
  map[x][y].reset();
  map[x][y] = blank.clone();
  
  setStartPosition(Point(x, y));
}

bool Map::validStart(int x, int y, bool *wall) {
  if (validPosition(x, y)) {
    auto subject = map[x][y];
    if (!subject->isPassable()) {
      *wall = true;
      if (std::dynamic_pointer_cast<Wall>(subject)->getType() == '#') {
        return true;
      }
    }
  }
  return false;
}

bool Map::validPosition(int x, int y) {
  if (x >= 0 && x < height && y >= 0 && y < width) {
    return true;
  }
  return false;
}

bool Map::validPosition(const Point &point) {
  if (point.x >= 0 && point.x < height && point.y >= 0 && point.y < width) {
    return true;
  }
  return false;
}

std::list<Point> Map::neighbouringFields(int x, int y) { //? leak
  // nebo jen queue? nebo array?
  std::list<Point> neighbours;
  if (validPosition(x + 1, y)) {
    neighbours.push_front(Point(x + 1, y));
  }
  if (validPosition(x - 1, y)) {
    neighbours.push_front(Point(x - 1, y));
  }
  if (validPosition(x, y + 1)) {
    neighbours.push_front(Point(x, y + 1));
  }
  if (validPosition(x, y - 1)) {
    neighbours.push_front(Point(x, y - 1));
  }
  return neighbours;
}

void Map::initVisitedMap(std::map<Point, bool> &visited) {
  for (int x = 0; x < height; x++) {
    for (int y = 0; y < width; y++) {
      visited[Point(x, y)] = false;
    }
  }
}

std::list<Point> Map::reconstructPath(const std::map<Point, Point> &prev, const Point &start) {
  
  std::list<Point> route;
  
  Point current = endPosition;
  while (current != start) {
    route.push_front(current);
    current = (*prev.find(current)).second;
  }
  route.push_front(start);
  return route;
}

std::list<Point> Map::reconstructPath(const std::map<Point, Point> &prev) {
  
  std::list<Point> route;
  
  Point current = endPosition;
  while (current != startPosition) {
    route.push_front(current);
    current = (*prev.find(current)).second;
  }
  route.push_front(startPosition);
  
  return route;
}

void Map::initMap(std::ifstream &file) {
  std::string mapDimensions;
  getline(file, mapDimensions);
  std::istringstream iss(mapDimensions);
  int h, w;
  iss >> h >> w;
  
  height = h;
  width = w;
  map.resize(height, std::vector<std::shared_ptr<Field >>(width));
}

void Map::fillBlankMap(std::ifstream &file, std::list<std::shared_ptr<Field>> &towers) {
  initMap(file);
  
  char c;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      file.get(c);
      if (c == '\n') {
        file.get(c);
      }
      if (c == '#') {
        Wall wall(i, j);
        map[i][j] = wall.clone();
      } else if (c == 'X') {
        Wall wall(i, j, 'X');
        map[i][j] = wall.clone();
      } else if (c == ' ') {
        Blank blank(i, j);
        map[i][j] = blank.clone();
      } else if (c == 'e' && (i == 0 || j == 0 || i == height - 1 || j == width - 1)) {
        endPosition.set(i, j);
        
        Blank blank(i, j);
        map[i][j] = blank.clone();
      } else {
      
      }
    }
  }
}

std::list<Point> Map::findRoute(const Point &start, const Point &hypotheticalPoint) {
  std::list<Point> route;
  if (hypotheticalPoint == endPosition) {
    return route;
  }
  
  std::queue<Point> opened;
  std::map<Point, bool> visited;
  std::map<Point, Point> prev;
  initVisitedMap(visited);
  
  opened.push(start);
  
  while (!opened.empty()) {
    Point currentPosition = opened.front();
    opened.pop();
    visited[currentPosition] = true;
    
    std::list<Point> nextIndices = neighbouringFields(currentPosition.x, currentPosition.y);
    for (auto &neighbour : nextIndices) {
      
      if (neighbour == endPosition) {
        prev.insert(std::make_pair(neighbour, currentPosition));
        route = reconstructPath(prev);
        return route;
      }
      
      if (!visited[neighbour] && map[neighbour.x][neighbour.y]->isPassable() && hypotheticalPoint != neighbour) {
        opened.push(neighbour);
        prev.insert(std::make_pair(neighbour, currentPosition));
        visited[neighbour] = true;
      }
    }
    
    visited[currentPosition] = true;
  }
  return route;
}

void Map::setStartPosition(const Point &start) {
  startPosition = start;
  Blank blank(start.x, start.y);
  
  map[start.x][start.y].reset();
  map[start.x][start.y] = blank.clone();
}