#pragma once
#include "AbstractDay.h"
#include "IntProcessor.h"
#include <vector>
#include <queue>

class Day07 : public AbstractDay
{
public:
  Day07();

  void* parseInput(std::string& input) override;
  void runPart1(void* input) override;
  void runPart2(void* input) override;

private:
  static int phaseInput;
  static int processorCom;

  static std::queue<int> input0;
  static std::queue<int> input1;
  static std::queue<int> input2;
  static std::queue<int> input3;
  static std::queue<int> input4;

  static void opInputChained0(IntProcessor* proc, int modes);
  static void opOutputChained0(IntProcessor* proc, int modes);
  static void opInputChained1(IntProcessor* proc, int modes);
  static void opOutputChained1(IntProcessor* proc, int modes);
  static void opInputChained2(IntProcessor* proc, int modes);
  static void opOutputChained2(IntProcessor* proc, int modes);
  static void opInputChained3(IntProcessor* proc, int modes);
  static void opOutputChained3(IntProcessor* proc, int modes);
  static void opInputChained4(IntProcessor* proc, int modes);
  static void opOutputChained4(IntProcessor* proc, int modes);
  static void opInputChained(IntProcessor* proc, int modes, int input);
  static int opOutputChained(IntProcessor* proc, int modes);
  static void opInput(IntProcessor* proc, int modes);
  static void opOutput(IntProcessor* proc, int modes);
};

