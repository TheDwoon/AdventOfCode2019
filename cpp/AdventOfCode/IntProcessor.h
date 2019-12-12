#pragma once
#include <map>

typedef void (*InstructionExecutor)(IntProcessor*);

class IntProcessor
{
private:
  int* m_memory;
  int* pc;
  std::map<int, InstructionExecutor> m_instructions;

public:

  void runProgram();
  void runInstruction();
  int getDigit(int x, int digit);
  int resolveRead(int* addr, int mode);
  int* resolveWrite(int* addr, int mode);
};

