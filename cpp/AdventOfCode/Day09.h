#pragma once
#include "AbstractDay.h"
#include "IntProcessor.h"

class Day09 : public AbstractDay
{
public:
  Day09();

  void* parseInput(std::string& input) override;
  void runPart1(void* input) override;
  void runPart2(void* input) override;

private:
  static void opInputTestMode(IntProcessor* proc, int modes);
  static void opInputBoostMode(IntProcessor* proc, int modes);
};

