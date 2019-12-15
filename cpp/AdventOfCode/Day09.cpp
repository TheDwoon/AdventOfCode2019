#include "Day09.h"
#include <iostream>
#include <vector>
#include <sstream>

Day09::Day09() : AbstractDay("input/input09.txt")
{
}

void* Day09::parseInput(std::string& input)
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

void Day09::runPart1(void* input)
{
  std::vector<int>* vector = (std::vector<int>*)input;

  IntProcessor proc(vector->data(), vector->size(), 1024);
  proc.registerInstruction(3, &Day09::opInputTestMode);
  proc.runProgram();
}

void Day09::runPart2(void* input)
{
  std::vector<int>* vector = (std::vector<int>*)input;

  IntProcessor proc(vector->data(), vector->size(), 1024);
  proc.registerInstruction(3, &Day09::opInputBoostMode);
  proc.runProgram();
}

void Day09::opInputTestMode(IntProcessor* proc, int modes)
{
  IntProcessor::performProcessorInput(proc, modes, 1);
}

void Day09::opInputBoostMode(IntProcessor* proc, int modes)
{
  IntProcessor::performProcessorInput(proc, modes, 2);
}
