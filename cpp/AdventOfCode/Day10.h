#pragma once
#include "AbstractDay.h"
#include <vector>

struct Location {
  Location(int x, int y) : x(x), y(y)
  {
  };

  int x;
  int y;
};

class Day10 : public AbstractDay
{
public:
  Day10();

  void* parseInput(std::string& input) override;
  void runPart1(void* input) override;
  void runPart2(void* input) override;

private:
  int evaluateLocation(Location& location, std::vector<Location>* locations);
};

