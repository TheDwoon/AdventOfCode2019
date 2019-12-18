#include "Day11.h"
#include <vector>
#include <sstream>
#include <iostream>

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

}

void Day11::runPart2(void* input)
{
}
