#include "Day07.h"
#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>

int Day07::phaseInput;
int Day07::processorCom;

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

  const int phases[] = {3, 1, 2, 4, 0};

  // set processor com to 0
  processorCom = 0;
  for (int i = 0; i < 5; i++)
  {
    phaseInput = phases[i];
    // copy memory for each processor
    int* memoryProc = new int[vector->size()];
    std::memcpy(memoryProc, vector->data(), sizeof(int) * vector->size());

    // create processors
    IntProcessor proc(memoryProc);
    proc.registerInstruction(3, &Day07::opInput);
    proc.registerInstruction(4, &Day07::opOutput);

    proc.runProgram();

    // free memory of processors
    delete[] memoryProc;
  }

  std::cout << "Final Output: " << processorCom << std::endl;
}

void Day07::runPart2(void* input)
{
}

void Day07::opInput(IntProcessor* proc, int modes)
{
  int modeA = proc->getMode(modes, 0);

  int* pc = proc->getPC();
  int* r = proc->resolveWrite(pc + 1, modeA);

  if (Day07::phaseInput > -1)
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
