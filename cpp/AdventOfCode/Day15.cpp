#include "Day15.h"
#include <sstream>
#include <iostream>
#include "IntProcessor.h"

struct Position {
  int x;
  int y;

  Position(int x = 0, int y = 0) {
    this->x = x;
    this->y = y;
  }

  Position north() {
    return Position(x, y - 1);
  }

  Position east() {
    return Position(x + 1, y);
  }

  Position south() {
    return Position(x, y + 1);
  }

  Position west() {
    return Position(x - 1, y);
  }
};

Day15::Day15() : AbstractDay("input/input15.txt")
{
}

void* Day15::parseInput(std::string& input)
{
  std::vector<int>* vector = new std::vector<int>();

  std::stringstream sstream(input);
  std::string buffer;
  while (std::getline(sstream, buffer, ',')) {
    int v;
    std::stringstream(buffer) >> v;
    vector->push_back(v);
  }

  return vector;
}

void Day15::runPart1(void* input)
{
  std::vector<int>* vector = (std::vector<int>*)input;

  IntProcessor proc(vector->data(), vector->size(), 1024);
  int64_t out;

  Map map(50, 50);  
  Position position(map.width / 2, map.height / 2);
  map.set(position.x, position.y, 1);

  std::deque<short> path = findPath(map, position.x, position.y, 3);
  int i = 0;
  while (!path.empty()) {
    proc << path.front();
    Position nextPosition;
    switch (path.front()) {
    case 1:
      nextPosition = position.north();
      break;
    case 2:
      nextPosition = position.south();
      break;
    case 3:
      nextPosition = position.west();
      break;
    case 4:
      nextPosition = position.east();
      break;
    }

    path.pop_front();
    proc >> out;

    map.set(nextPosition.x, nextPosition.y, out);
    if (out == 0) {
      path.clear();
    }
    else {
      position = nextPosition;
    }

    // if path is empty try to get to unknown terrain
    if (path.empty()) {
      path = findPath(map, position.x, position.y, 3);
    }
  }

  printMap(map);
  std::cout << "Path length: " << findPath(map, 25, 25, 2).size() << std::endl;
}

void Day15::runPart2(void* input)
{
  std::vector<int>* vector = (std::vector<int>*)input;

  IntProcessor proc(vector->data(), vector->size(), 1024);
}

void Day15::printMap(Map& map)
{
  for (int y = 0; y < map.height; y++) {
    for (int x = 0; x < map.width; x++) {
      switch (map.get(x, y))
      {
      case 0:
        std::cout << '#';
        break;
      case 1:
        std::cout << '.';
        break;
      case 2:
        std::cout << 'T';
        break;
      case 3:
      default:
        std::cout << '?';
      }
    }

    std::cout << std::endl;
  }
}

void Day15::printPath(Map& map) {
  for (int y = 0; y < map.height; y++) {
    for (int x = 0; x < map.width; x++) {
      short v = map.getPathing(x, y);
      if (v < 10) {
        std::cout << v;
      }
      /*else if (v < 100) {
        std::cout << v << "|";
      }
      else if (v < 1000) {
        std::cout << v << "|";
      }*/
      else {
        std::cout << " ";
      }      
    }

    std::cout << std::endl;
  }
}

struct PathState {
  
};

struct PState {
  int x;
  int y;
  int steps;

  PState(int x, int y, int steps): x(x), y(y), steps(steps) { }
};

std::deque<short> Day15::findPath(Map& map, int sX, int sY, int searchedObject)
{
  map.clearPathing();

  int tX = sX;
  int tY = sY;

  std::deque<PState> queue;
  queue.push_back(PState(sX, sY, 0));

  while (!queue.empty()) {
    PState& state = queue.front();
    if (state.steps < map.getPathing(state.x, state.y)) {
      map.setPathing(state.x, state.y, state.steps);

      if (map.get(state.x, state.y) == searchedObject) {
        tX = state.x;
        tY = state.y;
        break;
      }

      // check north
      if (state.y - 1 >= 0 && map.get(state.x, state.y - 1) != 0) {
        queue.push_back(PState(state.x, state.y - 1, state.steps + 1));
      }
      // check south
      if (state.y + 1 < map.height && map.get(state.x, state.y + 1) != 0) {
        queue.push_back(PState(state.x, state.y + 1, state.steps + 1));
      }
      // check west
      if (state.x - 1 >= 0 && map.get(state.x - 1, state.y) != 0) {
        queue.push_back(PState(state.x - 1, state.y, state.steps + 1));
      }
      // check east
      if (state.x + 1 < map.width && map.get(state.x + 1, state.y) != 0) {
        queue.push_back(PState(state.x + 1, state.y, state.steps + 1));
      }
    }

    queue.pop_front();
  }

  std::deque<short> path;
  while (tX != sX || tY != sY) {
    short currentValue = map.getPathing(tX, tY);
    if (tY - 1 >= 0 && map.getPathing(tX, tY - 1) == currentValue - 1) {
      tY -= 1;
      path.push_front(2);
    }
    else if (tY + 1 < map.height && map.getPathing(tX, tY + 1) == currentValue - 1) {
      tY += 1;
      path.push_front(1);
    }
    else if (tX - 1 >= 0 && map.getPathing(tX - 1, tY) == currentValue - 1) {
      tX -= 1;
      path.push_front(4);
    }
    else if (tX + 1 < map.width && map.getPathing(tX + 1, tY) == currentValue - 1) {
      tX += 1;
      path.push_front(3);
    }
  }

  return path;
}
