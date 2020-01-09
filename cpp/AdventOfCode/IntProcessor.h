#pragma once
#include <map>
#include <cstdint>
#include <functional>
#include <deque>

#define CHECK_BOUNDS

class IntProcessor
{
private:
  int64_t* m_memory;
  int64_t* m_pc;
  int64_t* m_relativeBase;
  int64_t m_memSize;
  bool m_suspended;
  std::map<int, std::function<void(IntProcessor*, int)>> m_instructions;
  
  std::deque<int64_t> m_inputs;
  std::deque<int64_t> m_outputs;

  // ready to use instructions
  static void opHalt(IntProcessor* proc, int modes);
  static void opAdd(IntProcessor* proc, int modes);
  static void opMultiply(IntProcessor* proc, int modes);
  void opInput(IntProcessor* proc, int modes);
  void opOutput(IntProcessor* proc, int modes);
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

  int64_t getOpCode() const;
  int getInstruction() const;
  int getModes() const;
  int getMode(int modes, int num);
  int64_t resolveRead(int64_t* addr, int mode);
  int64_t* resolveWrite(int64_t* addr, int mode);

  int64_t* getPC();
  void setPC(int64_t* pc);
  int64_t* getMemory();
  int64_t* getRelativeBase();
  void setRelativeBase(int64_t* relativeBase);

  bool isOutputReady();
  bool isSuspended();
  bool isHalted();
  void suspend(bool suspend = true);

  friend IntProcessor& operator<< (IntProcessor& proc, int64_t input);
  friend IntProcessor& operator>> (IntProcessor& proc, int64_t& output);

  static void performProcessorInput(IntProcessor* proc, int modes, int64_t input);
  static int64_t performProcessorOutput(IntProcessor* proc, int modes);

  static const int OP_ADD = 1;
  static const int OP_MULT = 2;
  static const int OP_INPUT = 3;
  static const int OP_OUTPUT = 4;
  static const int OP_JUMP_IF_TRUE = 5;
  static const int OP_JUMP_IF_FALSE = 6;
  static const int OP_LESS_THAN = 7;
  static const int OP_EQUALS = 8;
  static const int OP_MODIFY_RELATIVE_BASE = 9;

  static const int OP_HALT = 99;
};
