#pragma once
#include "AbstractDay.h"
#include <cstdio>
#include <string>

class Day05 : public virtual AbstractDay
{
public:
  Day05();

  void* parseInput(std::string& input) override;
  void runPart1(void* input) override;
  void runPart2(void* input) override;
};

