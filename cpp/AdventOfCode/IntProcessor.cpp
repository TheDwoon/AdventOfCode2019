#include "IntProcessor.h"
#include <math.h>
#include <iostream>

void IntProcessor::opHalt(IntProcessor* proc, int modes)
{
  // no op
}

void IntProcessor::opAdd(IntProcessor* proc, int modes)
{
  const int modeA = proc->getMode(modes, 0);
  const int modeB = proc->getMode(modes, 1);
  const int modeC = proc->getMode(modes, 2);

  int* pc = proc->getPC();
  int a = proc->resolveRead(pc + 1, modeA);
  int b = proc->resolveRead(pc + 2, modeB);
  int* r = proc->resolveWrite(pc + 3, modeC);
  *r = a + b;
  proc->setPC(pc + 4);
}

void IntProcessor::opMultiply(IntProcessor* proc, int modes)
{
  const int modeA = proc->getMode(modes, 0);
  const int modeB = proc->getMode(modes, 1);
  const int modeC = proc->getMode(modes, 2);

  int* pc = proc->getPC();
  int a = proc->resolveRead(pc + 1, modeA);
  int b = proc->resolveRead(pc + 2, modeB);
  int* r = proc->resolveWrite(pc + 3, modeC);
  *r = a * b;
  proc->setPC(pc + 4);
}

void IntProcessor::opOutput(IntProcessor* proc, int modes)
{
  int modeA = proc->getMode(modes, 0);

  int* pc = proc->getPC();
  int a = proc->resolveRead(pc + 1, modeA);
  std::cout << "Processor: " << a << std::endl;
  proc->setPC(pc + 2);
}

void IntProcessor::opJumpIfTrue(IntProcessor* proc, int modes)
{
  int modeA = proc->getMode(modes, 0);
  int modeB = proc->getMode(modes, 1);

  int* pc = proc->getPC();
  int a = proc->resolveRead(pc + 1, modeA);
  int b = proc->resolveRead(pc + 2, modeB);
  if (a != 0)
  {
    proc->setPC(proc->getMemory() + b);
  }
  else
  {
    proc->setPC(pc + 3);
  }
}

void IntProcessor::opJumpIfFalse(IntProcessor* proc, int modes)
{
  int modeA = proc->getMode(modes, 0);
  int modeB = proc->getMode(modes, 1);

  int* pc = proc->getPC();
  int a = proc->resolveRead(pc + 1, modeA);
  int b = proc->resolveRead(pc + 2, modeB);
  if (a == 0)
  {
    proc->setPC(proc->getMemory() + b);
  }
  else
  {
    proc->setPC(pc + 3);
  }
}

void IntProcessor::opLessThan(IntProcessor* proc, int modes)
{
  int modeA = proc->getMode(modes, 0);
  int modeB = proc->getMode(modes, 1);
  int modeC = proc->getMode(modes, 2);

  int* pc = proc->getPC();
  int a = proc->resolveRead(pc + 1, modeA);
  int b = proc->resolveRead(pc + 2, modeB);
  int* r = proc->resolveWrite(pc + 3, modeC);
  if (a < b)
  {
    *r = 1;
  }
  else
  {
    *r = 0;
  }

  proc->setPC(pc + 4);
}

void IntProcessor::opEquals(IntProcessor* proc, int modes)
{
  int modeA = proc->getMode(modes, 0);
  int modeB = proc->getMode(modes, 1);
  int modeC = proc->getMode(modes, 2);

  int* pc = proc->getPC();
  int a = proc->resolveRead(pc + 1, modeA);
  int b = proc->resolveRead(pc + 2, modeB);
  int* r = proc->resolveWrite(pc + 3, modeC);
  if (a == b)
  {
    *r = 1;
  }
  else
  {
    *r = 0;
  }

  proc->setPC(pc + 4);
}

IntProcessor::IntProcessor(int* memory) : m_memory(memory), m_pc(memory)
{
  registerInstruction(1, &IntProcessor::opAdd);
  registerInstruction(2, &IntProcessor::opMultiply);

  registerInstruction(4, &IntProcessor::opOutput);
  registerInstruction(5, &IntProcessor::opJumpIfTrue);
  registerInstruction(6, &IntProcessor::opJumpIfFalse);
  registerInstruction(7, &IntProcessor::opLessThan);
  registerInstruction(8, &IntProcessor::opEquals);

  registerInstruction(99, &IntProcessor::opHalt);
}

void IntProcessor::registerInstruction(int instructionCode, InstructionExecutor executor)
{
  m_instructions[instructionCode] = executor;
}

void IntProcessor::runProgram()
{
  int* oldPC = nullptr;
  int* newPC = nullptr;
  do {
    oldPC = m_pc;
    runInstruction();
    newPC = m_pc;
  } while (oldPC != newPC);
}

void IntProcessor::runInstruction()
{
  const int opCode = *m_pc;
  const int instructionCode = opCode % 100;
  const int modes = opCode / 100;

  InstructionExecutor executor = m_instructions.at(instructionCode);
  executor(this, modes);
}

int IntProcessor::getMode(int modes, int num)
{
  int e = static_cast<int>(pow(10, num));
  return (modes / e) % 10;
}

int IntProcessor::resolveRead(int* addr, int mode)
{
  switch (mode) {
  case 0:
    return m_memory[*addr];
  case 1:
    return *addr;
  default:
    return 0;
  }
}

int* IntProcessor::resolveWrite(int* addr, int mode)
{
  switch (mode)
  {
  case 0:
    return m_memory + *addr;
  default:
    return nullptr;
  }
}

int* IntProcessor::getPC()
{
  return m_pc;
}

void IntProcessor::setPC(int* pc)
{
  m_pc = pc;
}

int* IntProcessor::getMemory()
{
  return m_memory;
}

