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

void IntProcessor::opInput(IntProcessor* proc, int modes) {
  if(m_inputs.size() > 0)
  {
    int64_t input = m_inputs.front();
    m_inputs.pop_front();
    IntProcessor::performProcessorInput(proc, modes, input);
  }
  else
  {
    // no inputs -> suspend processor
    proc->suspend(true);
  }
}

void IntProcessor::opOutput(IntProcessor* proc, int modes)
{
  int modeA = proc->getMode(modes, 0);

  int64_t* pc = proc->getPC();
  int64_t a = proc->resolveRead(pc + 1, modeA);
  m_outputs.push_back(a);
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

IntProcessor::IntProcessor(int* memory, unsigned long size, unsigned long additonalMemory) : m_suspended(false), m_memSize(size + additonalMemory)
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
  registerInstruction(IntProcessor::OP_INPUT, std::bind(&IntProcessor::opInput, this, std::placeholders::_1, std::placeholders::_2));
  registerInstruction(IntProcessor::OP_OUTPUT, std::bind(&IntProcessor::opOutput, this, std::placeholders::_1, std::placeholders::_2));
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
  while (!isSuspended() && !isHalted())
  {
    runInstruction();
  }

  return isHalted();
}

void IntProcessor::runInstruction()
{
  const int64_t opCode = *m_pc;
  const int instructionCode = opCode % 100;
  const int modes = opCode / 100;

  std::function<void(IntProcessor*, int)> executor = m_instructions.at(instructionCode);
  executor(this, modes);
}

int64_t IntProcessor::getOpCode() const
{
  return *m_pc;
}

int IntProcessor::getInstruction() const
{
  return getOpCode() % 100;
}

int IntProcessor::getModes() const
{
  return getOpCode() / 100;
}

int IntProcessor::getMode(int modes, int num)
{
  int e = static_cast<int>(pow(10, num));
  return (modes / e) % 10;
}

int64_t IntProcessor::resolveRead(int64_t* addr, int mode)
{
  int64_t* readAddr = nullptr;

  switch (mode) {
  case 0:
    readAddr = m_memory + *addr;
    break;
  case 1:
    readAddr = addr;
    break;
  case 2:
    readAddr = m_relativeBase + *addr;
    break;
  default:
    return 0;
  }

#ifdef CHECK_BOUNDS
  if (readAddr < m_memory || readAddr >= m_memory + m_memSize)
  {
    std::cout << "READ OUT OF BOUNDS: [";
    std::cout << "readAddress = " << readAddr;
    std::cout << ", addr = " << addr;
    std::cout << ", mode = " << mode;
    std::cout << ", memStart = " << m_memory;
    std::cout << ", memEnd = " << m_memory + m_memSize;    
    std::cout << "]" << std::endl;
  }
#endif

  return *readAddr;
}

int64_t* IntProcessor::resolveWrite(int64_t* addr, int mode)
{
  int64_t* writeAddr = nullptr;

  switch (mode)
  {
  case 0:
    writeAddr = m_memory + *addr;
    break;
  case 1:
    // this case should not occur
    writeAddr = nullptr;
    break;
  case 2:
    writeAddr = m_relativeBase + *addr;
    break;
  default:
    return nullptr;
  }

#ifdef CHECK_BOUNDS
  if (writeAddr < m_memory || writeAddr >= m_memory + m_memSize)
  {
    std::cout << "WRITE OUT OF BOUNDS: [";
    std::cout << "writeAddress = " << writeAddr;
    std::cout << ", addr = " << addr;
    std::cout << ", mode = " << mode;
    std::cout << ", memStart = " << m_memory;
    std::cout << ", memEnd = " << m_memory + m_memSize;
    std::cout << "]" << std::endl;
  }
#endif // CHECK_BOUNDS


  return writeAddr;
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

bool IntProcessor::isSuspended()
{
  return m_suspended;
}

bool IntProcessor::isHalted()
{
  return getInstruction() == IntProcessor::OP_HALT;
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

IntProcessor& operator<<(IntProcessor& proc, int64_t input)
{
  proc.m_inputs.push_back(input);
  proc.suspend(false);

  return proc;
}

IntProcessor& operator>>(IntProcessor& proc, int64_t& output)
{
  if (proc.m_outputs.empty())
    proc.runProgram();

  if (proc.m_outputs.empty())
  {
    std::cout << "Empty processor output accessed!" << std::endl;
    output = 0;
    return proc;
  }

  output = proc.m_outputs.front();
  proc.m_outputs.pop_front();
  return proc;
}
