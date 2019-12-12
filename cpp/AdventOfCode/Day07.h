#pragma once
#include "AbstractDay.h"
#include "IntProcessor.h"
#include <vector>

class Day07 : AbstractDay
{
public:
  Day07();

  void* parseInput(std::string& input) override;
  void runPart1(void* input) override;
  void runPart2(void* input) override;

private:
  static int phaseInput;
  static int processorCom;
  static void opInput(IntProcessor* proc, int modes);
  static void opOutput(IntProcessor* proc, int modes);
};

