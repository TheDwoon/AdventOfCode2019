#pragma once
#include "AbstractDay.h"

class Day15 : public AbstractDay
{
public:
  Day15();

  void* parseInput(std::string& input) override;
  void runPart1(void* input) override;
  void runPart2(void* input) override;
};

