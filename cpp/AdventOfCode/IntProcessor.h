#pragma once
#include <map>

class IntProcessor;
typedef void (*InstructionExecutor)(IntProcessor*, int modes);

class IntProcessor
{
private:
  int* m_memory;
  int* m_pc;
  std::map<int, InstructionExecutor> m_instructions;

  // ready to use instructions
  static void opHalt(IntProcessor* proc, int modes);
  static void opAdd(IntProcessor* proc, int modes);
  static void opMultiply(IntProcessor* proc, int modes);
  static void opOutput(IntProcessor* proc, int modes);
  static void opJumpIfTrue(IntProcessor* proc, int modes);
  static void opJumpIfFalse(IntProcessor* proc, int modes);
  static void opLessThan(IntProcessor* proc, int modes);
  static void opEquals(IntProcessor* proc, int modes);

public:
  IntProcessor(int* m_memory);
  void registerInstruction(int instructionCode, InstructionExecutor executor);
  void runProgram();
  void runInstruction();
  int getMode(int modes, int num);
  int resolveRead(int* addr, int mode);
  int* resolveWrite(int* addr, int mode);
  int* getPC();
  void setPC(int* pc);
  int* getMemory();
};
