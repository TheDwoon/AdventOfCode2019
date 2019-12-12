#pragma once
#include "AbstractDay.h"
#include "IntProcessor.h"
#include <cstdio>
#include <string>

struct intprocessor {
  int* memory = nullptr;
  int* pc = nullptr;
};

class Day05 : public virtual AbstractDay
{
public:
  Day05();

  void* parseInput(std::string& input) override;
  void runPart1(void* input) override;
  void runPart2(void* input) override;

private:
  int m_input;

  static void opInputTask1(IntProcessor* proc, int modes);
  static void opInputTask2(IntProcessor* proc, int modes);
};

