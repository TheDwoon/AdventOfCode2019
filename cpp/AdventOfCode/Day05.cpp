#include "Day05.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

Day05::Day05() : AbstractDay("input/input05.txt"), m_input(1)
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

  IntProcessor proc(vector->data(), vector->size());
  proc.registerInstruction(3, &Day05::opInputTask1);

  proc.runProgram();
}

void Day05::runPart2(void* input)
{
  std::vector<int>* vector = (std::vector<int>*) input;

  IntProcessor proc(vector->data(), vector->size());
  proc.registerInstruction(3, &Day05::opInputTask2);

  proc.runProgram();
}

void Day05::opInputTask1(IntProcessor* proc, int modes)
{
  int modeA = proc->getMode(modes, 0);

  int64_t* pc = proc->getPC();
  int64_t* r = proc->resolveWrite(pc + 1, modeA);

  *r = 1;
  proc->setPC(pc + 2);
}

void Day05::opInputTask2(IntProcessor* proc, int modes)
{
  int modeA = proc->getMode(modes, 0);

  int64_t* pc = proc->getPC();
  int64_t* r = proc->resolveWrite(pc + 1, modeA);
  *r = 5;
  proc->setPC(pc + 2);
}
