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

  int64_t* pc = proc->getPC();
  int64_t a = proc->resolveRead(pc + 1, modeA);
  int64_t b = proc->resolveRead(pc + 2, modeB);
  int64_t* r = proc->resolveWrite(pc + 3, modeC);
  *r = a + b;
  proc->setPC(pc + 4);
}

void IntProcessor::opMultiply(IntProcessor* proc, int modes)
{
  const int modeA = proc->getMode(modes, 0);
  const int modeB = proc->getMode(modes, 1);
  const int modeC = proc->getMode(modes, 2);

  int64_t* pc = proc->getPC();
  int64_t a = proc->resolveRead(pc + 1, modeA);
  int64_t b = proc->resolveRead(pc + 2, modeB);
  int64_t* r = proc->resolveWrite(pc + 3, modeC);
  *r = a * b;
  proc->setPC(pc + 4);
}

void IntProcessor::opOutput(IntProcessor* proc, int modes)
{
  int modeA = proc->getMode(modes, 0);

  int64_t* pc = proc->getPC();
  int64_t a = proc->resolveRead(pc + 1, modeA);
  std::cout << "Processor: " << a << std::endl;
  proc->setPC(pc + 2);
}

void IntProcessor::opJumpIfTrue(IntProcessor* proc, int modes)
{
  int modeA = proc->getMode(modes, 0);
  int modeB = proc->getMode(modes, 1);

  int64_t* pc = proc->getPC();
  int64_t a = proc->resolveRead(pc + 1, modeA);
  int64_t b = proc->resolveRead(pc + 2, modeB);
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

  int64_t* pc = proc->getPC();
  int64_t a = proc->resolveRead(pc + 1, modeA);
  int64_t b = proc->resolveRead(pc + 2, modeB);
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

  int64_t* pc = proc->getPC();
  int64_t a = proc->resolveRead(pc + 1, modeA);
  int64_t b = proc->resolveRead(pc + 2, modeB);
  int64_t* r = proc->resolveWrite(pc + 3, modeC);
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

  int64_t* pc = proc->getPC();
  int64_t a = proc->resolveRead(pc + 1, modeA);
  int64_t b = proc->resolveRead(pc + 2, modeB);
  int64_t* r = proc->resolveWrite(pc + 3, modeC);
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

void IntProcessor::opModifyRelativeBase(IntProcessor* proc, int modes)
{
  int modeA = proc->getMode(modes, 0);

  int64_t* pc = proc->getPC();
  int64_t a = proc->resolveRead(pc + 1, modeA);

  //std::cout << "Modify relative base: " << proc->getRelativeBase() << "+" << a << std::endl;
  proc->setRelativeBase(proc->getRelativeBase() + a);
  proc->setPC(pc + 2);
}

IntProcessor::IntProcessor(int* memory, unsigned long size, unsigned long additonalMemory) : m_suspended(false)
{
  m_memory = new int64_t[size + additonalMemory];
  for (unsigned long i = 0; i < size; i++)
    m_memory[i] = static_cast<int64_t>(memory[i]);
  for (unsigned long i = size; i < size + additonalMemory; i++)
    m_memory[i] = 0;

  m_pc = m_memory;
  m_relativeBase = m_memory;

  registerInstruction(IntProcessor::OP_ADD, &IntProcessor::opAdd);
  registerInstruction(IntProcessor::OP_MULT, &IntProcessor::opMultiply);

  registerInstruction(IntProcessor::OP_OUTPUT, &IntProcessor::opOutput);
  registerInstruction(IntProcessor::OP_JUMP_IF_TRUE, &IntProcessor::opJumpIfTrue);
  registerInstruction(IntProcessor::OP_JUMP_IF_FALSE, &IntProcessor::opJumpIfFalse);
  registerInstruction(IntProcessor::OP_LESS_THAN, &IntProcessor::opLessThan);
  registerInstruction(IntProcessor::OP_EQUALS, &IntProcessor::opEquals);
  registerInstruction(IntProcessor::OP_MODIFY_RELATIVE_BASE, &IntProcessor::opModifyRelativeBase);

  registerInstruction(IntProcessor::OP_HALT, &IntProcessor::opHalt);
}

IntProcessor::~IntProcessor()
{
  delete[] m_memory;
}

void IntProcessor::registerInstruction(int instructionCode, std::function<void(IntProcessor*, int)> executor)
{
  m_instructions[instructionCode] = executor;
}

bool IntProcessor::runProgram()
{
  bool run = false;
  int64_t* oldPC = nullptr;
  int64_t* newPC = nullptr;
  do {
    oldPC = m_pc;
    runInstruction();
    newPC = m_pc;
    run = run || oldPC != newPC;
  } while (oldPC != newPC && !m_suspended);

  return run;
}

void IntProcessor::runInstruction()
{
  const long opCode = *m_pc;
  const int instructionCode = opCode % 100;
  const int modes = opCode / 100;

  std::function<void(IntProcessor*, int)> executor = m_instructions.at(instructionCode);
  executor(this, modes);
}

int IntProcessor::getMode(int modes, int num)
{
  int e = static_cast<int>(pow(10, num));
  return (modes / e) % 10;
}

int64_t IntProcessor::resolveRead(int64_t* addr, int mode)
{
  switch (mode) {
  case 0:
    return m_memory[*addr];
  case 1:
    return *addr;
  case 2:
    return *(m_relativeBase + *addr);
  default:
    return 0;
  }
}

int64_t* IntProcessor::resolveWrite(int64_t* addr, int mode)
{
  switch (mode)
  {
  case 0:
    return m_memory + *addr;
  case 2:
    return m_relativeBase + *addr;
  default:
    return nullptr;
  }
}

int64_t* IntProcessor::getPC()
{
  return m_pc;
}

void IntProcessor::setPC(int64_t* pc)
{
  m_pc = pc;
}

int64_t* IntProcessor::getMemory()
{
  return m_memory;
}

int64_t* IntProcessor::getRelativeBase()
{
  return m_relativeBase;
}

void IntProcessor::setRelativeBase(int64_t* relativeBase)
{
  m_relativeBase = relativeBase;
}

void IntProcessor::suspend(bool suspend)
{
  m_suspended = suspend;
}

void IntProcessor::performProcessorInput(IntProcessor* proc, int modes, int64_t input)
{
  int modeA = proc->getMode(modes, 0);

  int64_t* pc = proc->getPC();
  int64_t* r = proc->resolveWrite(pc + 1, modeA);
  *r = input;

  proc->setPC(pc + 2);
}

int64_t IntProcessor::performProcessorOutput(IntProcessor* proc, int modes)
{
  int modeA = proc->getMode(modes, 0);

  int64_t* pc = proc->getPC();
  int64_t a = proc->resolveRead(pc + 1, modeA);  
  proc->setPC(pc + 2);

  return a;
}
