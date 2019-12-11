#include "Day05.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

Day05::Day05() : AbstractDay("input/input05.txt")
{
}

void* Day05::parseInput(std::string& input)
{
  std::vector<int> *vector = new std::vector<int>();

  std::stringstream sstream(input);
  std::string buffer;
  while (std::getline(sstream, buffer, ',')) {
    int v;
    std::stringstream(buffer) >> v;
    vector->push_back(v);
  }

  return vector;
}

void Day05::runPart1(void* input)
{
  std::vector<int>* vector = (std::vector<int>*) input;

  intprocessor proc;
  proc.memory = vector->data();
  proc.pc = proc.memory;

  m_input = 1;
  runProgram(proc);
}

void Day05::runPart2(void* input)
{
  std::vector<int>* vector = (std::vector<int>*) input;

  intprocessor proc;
  proc.memory = vector->data();
  proc.pc = proc.memory;

  m_input = 5;
  runProgram(proc);
}

void Day05::runProgram(intprocessor& proc)
{
  int* oldPC;
  int* newPC;
  do {
    oldPC = proc.pc;
    runInstruction(proc);
    newPC = proc.pc;

  } while (oldPC != newPC);
}

void Day05::runInstruction(intprocessor& proc)
{  
  const int opCode = *proc.pc;
  const int instCode = opCode % 100;
  const int modes = opCode / 100;
  const int modeA = getDigit(modes, 0);
  const int modeB = getDigit(modes, 1);
  const int modeC = getDigit(modes, 2);

  switch (instCode) {
  case 1: {
    // ADD Instruction
    const int a = resolveRead(proc, proc.pc + 1, modeA);
    const int b = resolveRead(proc, proc.pc + 2, modeB);
    int* r = resolveWrite(proc, proc.pc + 3, modeC);    
    *r = a + b;
    proc.pc += 4;
    return;
  }
  case 2: {
    // MULTIPLY Instruction
    const int a = resolveRead(proc, proc.pc + 1, modeA);
    const int b = resolveRead(proc, proc.pc + 2, modeB);
    int* r = resolveWrite(proc, proc.pc + 3, modeC);
    *r = a * b;
    proc.pc += 4;
    return;
  }
  case 3: {
    // INPUT Instruction
    int* r = resolveWrite(proc, proc.pc + 1, modeA);
    *r = resolveInput();
    proc.pc += 2;
    return;
  }
  case 4: {
    // OUTPUT Instruction
    const int a = resolveRead(proc, proc.pc + 1, modeA);
    resolveOutput(a);
    proc.pc += 2;
    return;
  }
  case 5: {
    // JUMP-IF-TRUE Instruction
    const int a = resolveRead(proc, proc.pc + 1, modeA);
    const int b = resolveRead(proc, proc.pc + 2, modeB);
    if (a != 0)
    {
      proc.pc = proc.memory + b;
    }
    else
    {
      proc.pc += 3;
    }
    return;
  }
  case 6: {
    // JUMP-IF-FALSE Instruction
    const int a = resolveRead(proc, proc.pc + 1, modeA);
    const int b = resolveRead(proc, proc.pc + 2, modeB);
    if (a == 0)
    {
      proc.pc = proc.memory + b;
    }
    else
    {
      proc.pc += 3;
    }
    return;
  }
  case 7: {
    // LESS-THAN Instruction
    const int a = resolveRead(proc, proc.pc + 1, modeA);
    const int b = resolveRead(proc, proc.pc + 2, modeB);
    int* r = resolveWrite(proc, proc.pc + 3, modeC);    
    if (a < b) {
      *r = 1;
    }
    else {
      *r = 0;
    }

    proc.pc += 4;
    return;
  }
  case 8: {
    // EQUALS Instruction
    const int a = resolveRead(proc, proc.pc + 1, modeA);
    const int b = resolveRead(proc, proc.pc + 2, modeB);
    int* r = resolveWrite(proc, proc.pc + 3, modeC);    
    if (a == b)
    {
      *r = 1;
    }
    else
    {
      *r = 0;
    }

    proc.pc += 4;
    return;
  }
  case 99:
    // HALT Instruction
    return;
  }
}

int Day05::resolveInput()
{
  return m_input;
}

void Day05::resolveOutput(int x)
{
  std::cout << "Processor: " << x << std::endl;
}

int Day05::getDigit(int x, int digit)
{
  int e = static_cast<int>(pow(10, digit));
  return (x / e) % 10;
}

int* Day05::resolveWrite(intprocessor& proc, int* param, int mode)
{
  if (mode == 0)
  {
    return proc.memory + *param;
  }
  
  return nullptr;
}

int Day05::resolveRead(intprocessor& proc, int* param, int mode)
{
  if (mode == 0) {
    return proc.memory[*param];
  }
  else if (mode == 1)
  {
    return *param;
  }
  return 0;
}
