#pragma once
#include "AbstractDay.h"

class Day11 : public AbstractDay
{
public:
  Day11();

  void* parseInput(std::string& input) override;
  void runPart1(void* input) override;
  void runPart2(void* input) override;
};

