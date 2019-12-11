#pragma once
#include "AbstractDay.h"
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

  void runProgram(intprocessor& proc);
  void runInstruction(intprocessor& proc);
  int getDigit(int x, int digit);
  int* resolveWrite(intprocessor& proc, int* param, int mode);
  int resolveRead(intprocessor& proc, int* param, int mode);  
  int resolveInput();
  void resolveOutput(int x);
};

