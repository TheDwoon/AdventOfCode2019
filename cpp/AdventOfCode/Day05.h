#pragma once
#include "AbstractDay.h"
#include <cstdio>
#include <string>

class Day05 : public virtual AbstractDay<int>
{
public:
  Day05();

  int* parseInput(std::string& input) override;
  void runPart1(int* input) override;
  void runPart2(int* input) override;
};

