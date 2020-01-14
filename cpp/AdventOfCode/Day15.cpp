#include "Day15.h"
#include <vector>
#include <sstream>
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
}

void Day15::runPart2(void* input)
{
  std::vector<int>* vector = (std::vector<int>*)input;

  IntProcessor proc(vector->data(), vector->size(), 1024);
}
