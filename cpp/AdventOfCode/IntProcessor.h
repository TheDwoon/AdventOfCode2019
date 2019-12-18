#pragma once
#include <map>
#include <cstdint>
#include <functional>

//template <typename T>
//using InstructionExecutor = void (*)(IntProcessor<T>*, int modes);

class IntProcessor
{
private:
  int64_t* m_memory;
  int64_t* m_pc;
  int64_t* m_relativeBase;
  bool m_suspended;
  std::map<int, std::function<void(IntProcessor*, int)>> m_instructions;

  // ready to use instructions
  static void opHalt(IntProcessor* proc, int modes);
  static void opAdd(IntProcessor* proc, int modes);
  static void opMultiply(IntProcessor* proc, int modes);
  static void opOutput(IntProcessor* proc, int modes);
  static void opJumpIfTrue(IntProcessor* proc, int modes);
  static void opJumpIfFalse(IntProcessor* proc, int modes);
  static void opLessThan(IntProcessor* proc, int modes);
  static void opEquals(IntProcessor* proc, int modes);
  static void opModifyRelativeBase(IntProcessor* proc, int modes);

public:
  IntProcessor(int* m_memory, unsigned long size, unsigned long additonalMemory = 0);
  virtual ~IntProcessor();
  void registerInstruction(int instructionCode, std::function<void(IntProcessor*, int)> executor);
  bool runProgram();
  void runInstruction();
  int getMode(int modes, int num);
  int64_t resolveRead(int64_t* addr, int mode);
  int64_t* resolveWrite(int64_t* addr, int mode);
  int64_t* getPC();
  void setPC(int64_t* pc);
  int64_t* getMemory();
  int64_t* getRelativeBase();
  void setRelativeBase(int64_t* relativeBase);
  void suspend(bool suspend = true);

  static void performProcessorInput(IntProcessor* proc, int modes, int64_t input);
};
