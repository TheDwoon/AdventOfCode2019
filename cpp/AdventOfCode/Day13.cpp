#include "Day13.h"
#include <sstream>
#include <vector>
#include <iostream>
#include "IntProcessor.h"

Day13::Day13() : AbstractDay("input/input13.txt")
{
}

void* Day13::parseInput(std::string& input)
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

void Day13::runPart1(void* input)
{
  std::vector<int>* vector = (std::vector<int>*)input;

  IntProcessor proc(vector->data(), vector->size(), 1024);

  int64_t x, y, tileId;
  int blocksOnScreen = 0;
  while (!proc.isHalted() || proc.isOutputReady()) {
    proc >> x >> y >> tileId;
    if (tileId == 2)
      blocksOnScreen++;
  }

  std::cout << "Block on screen: " << blocksOnScreen << std::endl;
}

void Day13::runPart2(void* input)
{
  std::vector<int>* vector = (std::vector<int>*)input;
  (*vector)[0] = 2;

  IntProcessor proc(vector->data(), vector->size(), 1024);

  int64_t x, y, tileId;
  int64_t score = 0;
  int64_t ballX = 0;
  int64_t playerX = 0;

  while (!proc.isHalted()) {
    proc.runProgram();

    while (proc.isOutputReady()) {
      proc >> x >> y >> tileId;
      if (x == -1) {
        score = tileId;
      }
      else {
        if (tileId == 3) {
          playerX = x;
        }
        else if (tileId == 4) {
          ballX = x;
        }
      }
    }

    if (ballX < playerX)
      proc << -1;
    else if (ballX > playerX)
      proc << 1;
    else
      proc << 0;
  }

  std::cout << "Score: " << score << std::endl;
}
