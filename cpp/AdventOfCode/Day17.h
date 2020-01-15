#pragma once
#include "AbstractDay.h"
class Day17 :	public AbstractDay
{
public:
  Day17();

  void* parseInput(std::string& input) override;
  void runPart1(void* input) override;
  void runPart2(void* input) override;
};

