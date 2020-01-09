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

  const int screenWidth = 39;
  const int screenHeight = 21;
  short screen[screenHeight][screenWidth];
  for (int y = 0; y < screenHeight; y++) {
    for (int x = 0; x < screenWidth; x++) {
      screen[y][x] = 0;
    }
  }

  IntProcessor proc(vector->data(), vector->size(), 1024);
  int64_t x, y, tileId;
  int blocksOnScreen = 0;
  while (!proc.isHalted() || proc.isOutputReady()) {
    proc >> x >> y >> tileId;
    if (tileId == 2)
      blocksOnScreen++;

    screen[y][x] = tileId;
  }

  for (int y = 0; y < screenHeight; y++) {
    for (int x = 0; x < screenWidth; x++) {
      short v = screen[y][x];
      char c;
      switch (v) {
      case 0:
        c = ' ';
        break;
      case 1:
        c = '#';
        break;
      case 2:
        c = 'X';
        break;
      case 3:
        c = '-';
        break;
      case 4:
        c = '*';
        break;
      default:
        c = '?';
        break;
      }

      std::cout << c;
    }

    std::cout << std::endl;
  }

  std::cout << "Block on screen: " << blocksOnScreen << std::endl;
}

void Day13::runPart2(void* input)
{
}
