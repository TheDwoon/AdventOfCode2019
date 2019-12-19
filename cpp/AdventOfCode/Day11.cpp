#include "Day11.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
#include "IntProcessor.h"

enum TileColor { BLACK, WHITE };

typedef char Facing;

struct Position {
  int x;
  int y;

  bool operator<(const Position& other) const {
    if (x == other.x)
      return y < other.y;
    else
      return x < other.x;
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
      TileColor paintColor = output == 0 ? TileColor::BLACK : TileColor::WHITE;
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
        position.y++;
        break;
      case LEFT:
        position.x--;
        break;
      case DOWN:
        position.y--;
        break;
      case RIGHT:
        position.x++;
        break;
      }

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
  IntProcessor proc(vector->data(), vector->size());

  proc.registerInstruction(IntProcessor::OP_INPUT, std::bind(&HullRobot::opInput, &robot, std::placeholders::_1, std::placeholders::_2));
  proc.registerInstruction(IntProcessor::OP_OUTPUT, std::bind(&HullRobot::opOutput, &robot, std::placeholders::_1, std::placeholders::_2));

  proc.runProgram();

  Position p1;
  Position p2;
  bool a = p1 < p2;

  std::cout << "Painted tiles: " << robot.paintedAtLeastOnce << std::endl;
}

void Day11::runPart2(void* input)
{
}
