#include "Day07.h"
#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>

Day07::Day07() : AbstractDay("input/input07.txt")
{
}

void* Day07::parseInput(std::string& input)
{
  std::vector<int>* vector = new std::vector<int>();

  std::stringstream sstream(input);
  std::string buffer;
  while (std::getline(sstream, buffer, ',')) {
    int v;
    std::stringstream(buffer) >> v;
    vector->push_back(v);
  }

  return vector;
}

void Day07::runPart1(void* input)
{
  std::vector<int>* vector = (std::vector<int>*) input;

  int* memoryProc0 = new int[vector->size()];
  std::memcpy(memoryProc0, vector->data(), sizeof(int) * vector->size());
  int* memoryProc1 = new int[vector->size()];
  std::memcpy(memoryProc1, vector->data(), sizeof(int) * vector->size());
  int* memoryProc2 = new int[vector->size()];
  std::memcpy(memoryProc2, vector->data(), sizeof(int) * vector->size());
  int* memoryProc3 = new int[vector->size()];
  std::memcpy(memoryProc3, vector->data(), sizeof(int) * vector->size());
  int* memoryProc4 = new int[vector->size()];
  std::memcpy(memoryProc4, vector->data(), sizeof(int) * vector->size());

  IntProcessor proc0(memoryProc0);
  IntProcessor proc1(memoryProc1);
  IntProcessor proc2(memoryProc2);
  IntProcessor proc3(memoryProc3);
  IntProcessor proc4(memoryProc4);

  delete[] memoryProc0;
  delete[] memoryProc1;
  delete[] memoryProc2;
  delete[] memoryProc3;
  delete[] memoryProc4;
}

void Day07::runPart2(void* input)
{
}

void Day07::opInput(IntProcessor* proc, int modes)
{
  int modeA = proc->getMode(modes, 0);

  int* pc = proc->getPC();
  int* r = proc->resolveWrite(pc + 1, modeA);

  if (phaseInput > -1)
  {
    std::cout << "Reading phase input: " << phaseInput << std::endl;
    *r = phaseInput;
    phaseInput = -1;
  }
  else
  {
    std::cout << "Reading from com: " << processorCom << std::endl;
    *r = processorCom;
  }
  
  proc->setPC(pc + 2);
}

void Day07::opOutput(IntProcessor* proc, int modes)
{
  int modeA = proc->getMode(modes, 0);

  int* pc = proc->getPC();
  int a = proc->resolveRead(pc + 1, modeA);
  std::cout << "Writing to com: " << a << std::endl;
  processorCom = a;
  proc->setPC(pc + 2);
}
