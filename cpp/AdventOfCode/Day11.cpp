#include "Day11.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
#include <algorithm>
#include "IntProcessor.h"

enum TileColor { BLACK, WHITE };

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
  std::map<Position, TileColor> tiles;
  int paintedAtLeastOnce = 0;

  void opInput(IntProcessor* proc, int modes)
  {
    TileColor color = TileColor::BLACK;
    auto it = tiles.find(position);
    if (it != tiles.end())
    {
      color = (*it).second;
    }

    if (color == TileColor::BLACK)
      IntProcessor::performProcessorInput(proc, modes, 0);
    else
      IntProcessor::performProcessorInput(proc, modes, 1);
  }

  int outputState = 0;
  void opOutput(IntProcessor* proc, int modes)
  {
    int64_t output = IntProcessor::performProcessorOutput(proc, modes);

    if (outputState == 0)
    {
      TileColor paintColor = ((output == 0) ? TileColor::BLACK : TileColor::WHITE);
      auto it = tiles.find(position);
      if (it == tiles.end())
        paintedAtLeastOnce++;

      tiles[position] = paintColor;

      outputState = 1;
    }
    else
    {
      facing += (output == 0) ? -1 : 1;
      if (facing < 0)
        facing += 4;
      else if (facing > 3)
        facing -= 4;

      switch (facing) {
      case UP:
        position.y--;
        break;
      case LEFT:
        position.x--;
        break;
      case DOWN:
        position.y++;
        break;
      case RIGHT:
        position.x++;
        break;
      }

      //std::cout << "Position (" << position.x << "|" << position.y << ")" << std::endl;

      outputState = 0;
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

  HullRobot robot;
  IntProcessor proc(vector->data(), vector->size(), 1024);

  proc.registerInstruction(IntProcessor::OP_INPUT, std::bind(&HullRobot::opInput, &robot, std::placeholders::_1, std::placeholders::_2));
  proc.registerInstruction(IntProcessor::OP_OUTPUT, std::bind(&HullRobot::opOutput, &robot, std::placeholders::_1, std::placeholders::_2));

  proc.runProgram();

  std::cout << "Painted tiles: " << robot.paintedAtLeastOnce << std::endl;
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

  for (int y = minY; y < maxY; y++) {
    for (int x = minX; x < maxX; x++) {
      auto it = robot.tiles.find(Position{ x, y });
      char c;
      if (it == robot.tiles.end())
        c = ' ';
      else
        c = it->second == TileColor::BLACK ? '.' : '#';

      std::cout << c;
    }

    std::cout << std::endl;
  }
}

void Day11::runPart2(void* input)
{
  std::vector<int>* vector = (std::vector<int>*)input;

  HullRobot robot;
  robot.tiles[Position{ 0, 0 }] = TileColor::WHITE;
  IntProcessor proc(vector->data(), vector->size(), 1024);

  proc.registerInstruction(IntProcessor::OP_INPUT, std::bind(&HullRobot::opInput, &robot, std::placeholders::_1, std::placeholders::_2));
  proc.registerInstruction(IntProcessor::OP_OUTPUT, std::bind(&HullRobot::opOutput, &robot, std::placeholders::_1, std::placeholders::_2));

  proc.runProgram();

  std::cout << "PT: " << robot.paintedAtLeastOnce << std::endl;
  
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

  for (int y = minY; y < maxY; y++) {
    for (int x = minX; x < maxX; x++) {
      auto it = robot.tiles.find(Position{ x, y });
      char c;
      if (it == robot.tiles.end())
        c = ' ';
      else
        c = it->second == TileColor::BLACK ? '.' : '#';

      std::cout << c;
    }

    std::cout << std::endl;
  }
}
