#include "Day11.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
#include <algorithm>
#include "IntProcessor.h"

typedef char Facing;

struct Position {
  int x;
  int y;

  bool operator<(const Position& other) const {
    if (y == other.y)
      return x < other.x;
    else
      return y < other.y;
  }
};

struct HullRobot {
  static const Facing UP = 0;
  static const Facing RIGHT = 1;
  static const Facing DOWN = 2;
  static const Facing LEFT = 3;

  Position position{0, 0};
  Facing facing = UP;
  std::map<Position, short> tiles;

  void turnLeft() {
    facing = (facing + 3) % 4;
  }

  void turnRight() {
    facing = (facing + 5) % 4;
  }

  void move() {
    switch (facing) {
    case UP:
      position.y -= 1;
      break;
    case DOWN:
      position.y += 1;
      break;
    case LEFT:
      position.x -= 1;
      break;
    case RIGHT:
      position.x += 1;
      break;
    }
  }
};

Day11::Day11() : AbstractDay("input/input11.txt")
{
}

void* Day11::parseInput(std::string& input)
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

void Day11::runPart1(void* input)
{
  std::vector<int>* vector = (std::vector<int>*)input;

  unsigned int paintedAtLeastOnce = 0;

  HullRobot robot;
  IntProcessor proc(vector->data(), vector->size(), 1024);
  
  int64_t paintColor;
  int64_t turnDirection;
  while (!proc.isHalted())
  {
    auto tileIt = robot.tiles.find(robot.position);
    if (tileIt == robot.tiles.end()) {
      paintedAtLeastOnce++;
      robot.tiles[robot.position] = 0;
    }

    proc << robot.tiles[robot.position];
    proc >> paintColor >> turnDirection;

    robot.tiles[robot.position] = paintColor;
    if (turnDirection == 0)
      robot.turnLeft();
    else if (turnDirection == 1)
      robot.turnRight();
    else
      std::cout << "Confused screaming: " << turnDirection << std::endl;

    robot.move();
  }

  std::cout << "Painted tiles: " << paintedAtLeastOnce << std::endl;
  int minX = INT_MAX;
  int maxX = INT_MIN;
  int minY = INT_MAX;
  int maxY = INT_MIN;

  for (auto it = robot.tiles.begin(); it != robot.tiles.end(); ++it) {
    Position pos = it->first;
    minX = std::min(minX, pos.x);
    maxX = std::max(maxX, pos.x);
    minY = std::min(minY, pos.y);
    maxY = std::max(maxY, pos.y);
  }

  std::cout << "x: " << minX << ", " << maxX << std::endl;
  std::cout << "y: " << minY << ", " << maxY << std::endl;

  if (robot.tiles.size() == 0)
    return;

  for (int y = minY; y <= maxY; y++) {
    for (int x = minX; x <= maxX; x++) {
      auto it = robot.tiles.find(Position{ x, y });
      char c;
      if (it == robot.tiles.end())
        c = ' ';
      else
        c = it->second == 0 ? '.' : '#';

      std::cout << c;
    }

    std::cout << std::endl;
  }
}

void Day11::runPart2(void* input)
{
  std::vector<int>* vector = (std::vector<int>*)input;

  HullRobot robot;
  robot.tiles[robot.position] = 1;
  IntProcessor proc(vector->data(), vector->size(), 1024);

  int64_t paintColor;
  int64_t turnDirection;
  while (!proc.isHalted())
  {    
    proc << robot.tiles[robot.position];
    proc >> paintColor >> turnDirection;

    robot.tiles[robot.position] = paintColor;
    if (turnDirection == 0)
      robot.turnLeft();
    else if (turnDirection == 1)
      robot.turnRight();
    else
      std::cout << "Confused screaming: " << turnDirection << std::endl;

    robot.move();
  }

  int minX = INT_MAX;
  int maxX = INT_MIN;
  int minY = INT_MAX;
  int maxY = INT_MIN;

  for (auto it = robot.tiles.begin(); it != robot.tiles.end(); ++it) {
    Position pos = it->first;
    minX = std::min(minX, pos.x);
    maxX = std::max(maxX, pos.x);
    minY = std::min(minY, pos.y);
    maxY = std::max(maxY, pos.y);
  }

  std::cout << "x: " << minX << ", " << maxX << std::endl;
  std::cout << "y: " << minY << ", " << maxY << std::endl;

  if (robot.tiles.size() == 0)
    return;

  for (int y = minY; y <= maxY; y++) {
    for (int x = minX; x <= maxX; x++) {
      auto it = robot.tiles.find(Position{ x, y });
      char c;
      if (it == robot.tiles.end())
        c = ' ';
      else
        c = it->second == 0 ? '.' : '#';

      std::cout << c;
    }

    std::cout << std::endl;
  }
}
