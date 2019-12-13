#include "Day07.h"
#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include <algorithm>

int Day07::phaseInput;
int Day07::processorCom;

std::queue<int> Day07::input0;
std::queue<int> Day07::input1;
std::queue<int> Day07::input2;
std::queue<int> Day07::input3;
std::queue<int> Day07::input4;

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

  int phases[] = {0, 1, 2, 3, 4};
  int maxCom = 0;
  do {
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

      if (processorCom > maxCom) {
        maxCom = processorCom;
      }
    }
  } while (std::next_permutation(phases, phases + 5));
  std::cout << "Day 7 > Part 1 " << maxCom << std::endl;
}

void Day07::runPart2(void* input)
{
  std::vector<int>* vector = (std::vector<int>*) input;

  int memory[] = { 3,52,1001,52,-5,52,3,53,1,52,56,54,1007,54,5,55,1005,55,26,1001,54,
-5,54,1105,1,12,1,53,54,53,1008,54,0,55,1001,55,1,55,2,53,55,53,4,
53,1001,56,-1,56,1005,56,6,99,0,0,0,0,10 };
  int phases[] = { 9,7,8,5,6 };
  int maxCom = 0;
  //do {
    // copy memory for each processor
    int* memoryProc0 = (int*)std::memcpy(new int[sizeof(memory)], memory, sizeof(memory));
    int* memoryProc1 = (int*)std::memcpy(new int[sizeof(memory)], memory, sizeof(memory));
    int* memoryProc2 = (int*)std::memcpy(new int[sizeof(memory)], memory, sizeof(memory));
    int* memoryProc3 = (int*)std::memcpy(new int[sizeof(memory)], memory, sizeof(memory));
    int* memoryProc4 = (int*)std::memcpy(new int[sizeof(memory)], memory, sizeof(memory));

    input0.push(phases[0]);
    input0.push(0);
    input1.push(phases[1]);
    input2.push(phases[2]);
    input3.push(phases[3]);
    input4.push(phases[4]);

    // create processors
    IntProcessor proc0(memoryProc0);
    proc0.registerInstruction(3, &Day07::opInputChained0);
    proc0.registerInstruction(4, &Day07::opOutputChained0);
    IntProcessor proc1(memoryProc1);
    proc1.registerInstruction(3, &Day07::opInputChained1);
    proc1.registerInstruction(4, &Day07::opOutputChained1);
    IntProcessor proc2(memoryProc2);
    proc2.registerInstruction(3, &Day07::opInputChained2);
    proc2.registerInstruction(4, &Day07::opOutputChained2);
    IntProcessor proc3(memoryProc3);
    proc3.registerInstruction(3, &Day07::opInputChained3);
    proc3.registerInstruction(4, &Day07::opOutputChained3);
    IntProcessor proc4(memoryProc4);
    proc4.registerInstruction(3, &Day07::opInputChained4);
    proc4.registerInstruction(4, &Day07::opOutputChained4);

    bool running = true;
    while (running)
    {
      running = false;
      if (!input0.empty())
      {
        proc0.suspend(false);
        running = proc0.runProgram();
      }
      if (!input1.empty())
      {
        proc1.suspend(false);
        running = proc1.runProgram();
      }
      if (!input2.empty())
      {
        proc2.suspend(false);
        running = proc2.runProgram();
      }
      if (!input3.empty())
      {
        proc3.suspend(false);
        running = proc3.runProgram();
      }
      if (!input4.empty())
      {
        proc4.suspend(false);
        running = proc4.runProgram();
      }
    }

    std::vector<int> results;
    while (!input0.empty())
    {
      results.push_back(input0.front());
      input0.pop();
    }
    while (!input1.empty())
    {
      results.push_back(input1.front());
      input1.pop();
    }
    while (!input2.empty())
    {
      results.push_back(input2.front());
      input2.pop();
    }
    while (!input3.empty())
    {
      results.push_back(input3.front());
      input3.pop();
    }
    while (!input4.empty())
    {
      results.push_back(input4.front());
      input4.pop();
    }

    std::cout << "Results: ";
    for (int i = 0; i < results.size(); i++)
    {
      std::cout << results[i] << " ";
    }
    std::cout << std::endl;

    // free memory of processors
    delete[] memoryProc0;
    delete[] memoryProc1;
    delete[] memoryProc2;
    delete[] memoryProc3;
    delete[] memoryProc4;
  //} while (std::next_permutation(phases, phases + 5));
  std::cout << "Day 7 > Part 1 " << maxCom << std::endl;
}

void Day07::opInputChained0(IntProcessor* proc, int modes)
{
  if (input0.empty())
  {
    proc->suspend();
  }
  else
  {
    int input = input0.front();
    input0.pop();
    std::cout << "READ Proc 0: " << input << std::endl;
    opInputChained(proc, modes, input);
  }
}

void Day07::opOutputChained0(IntProcessor* proc, int modes)
{
  int output = opOutputChained(proc, modes);
  input1.push(output);
  std::cout << "WRITE Proc 0: " << output << std::endl;
}


void Day07::opInputChained1(IntProcessor* proc, int modes)
{
  if (input1.empty())
  {
    proc->suspend();
  }
  else
  {
    int input = input1.front();
    input1.pop();
    std::cout << "READ Proc 1: " << input << std::endl;
    opInputChained(proc, modes, input);
  }
}

void Day07::opOutputChained1(IntProcessor* proc, int modes)
{
  int output = opOutputChained(proc, modes);
  input2.push(output);
}


void Day07::opInputChained2(IntProcessor* proc, int modes)
{
  if (input2.empty())
  {
    proc->suspend();
  }
  else
  {
    int input = input2.front();
    input2.pop();
    std::cout << "READ Proc 2: " << input << std::endl;
    opInputChained(proc, modes, input);
  }
}

void Day07::opOutputChained2(IntProcessor* proc, int modes)
{
  int output = opOutputChained(proc, modes);
  input3.push(output);
}


void Day07::opInputChained3(IntProcessor* proc, int modes)
{
  if (input3.empty())
  {
    proc->suspend();
  }
  else
  {
    int input = input3.front();
    input3.pop();
    std::cout << "READ Proc 3: " << input << std::endl;
    opInputChained(proc, modes, input);
  }
}

void Day07::opOutputChained3(IntProcessor* proc, int modes)
{
  int output = opOutputChained(proc, modes);
  input4.push(output);
}


void Day07::opInputChained4(IntProcessor* proc, int modes)
{
  if (input4.empty())
  {
    proc->suspend();
  }
  else
  {
    int input = input4.front();
    input4.pop();
    std::cout << "READ Proc 4: " << input << std::endl;
    opInputChained(proc, modes, input);
  }
}

void Day07::opOutputChained4(IntProcessor* proc, int modes)
{
  int output = opOutputChained(proc, modes);
  input0.push(output);
}

void Day07::opInputChained(IntProcessor* proc, int modes, int input)
{
  int modeA = proc->getMode(modes, 0);

  int* pc = proc->getPC();
  int* r = proc->resolveWrite(pc + 1, modeA);
  *r = input;

  proc->setPC(pc + 2);
}

int Day07::opOutputChained(IntProcessor* proc, int modes)
{
  int modeA = proc->getMode(modes, 0);

  int* pc = proc->getPC();
  int a = proc->resolveRead(pc + 1, modeA);
  proc->setPC(pc + 2);
  return a;
}

void Day07::opInput(IntProcessor* proc, int modes)
{
  int modeA = proc->getMode(modes, 0);

  int* pc = proc->getPC();
  int* r = proc->resolveWrite(pc + 1, modeA);

  if (Day07::phaseInput > -1)
  {
    //std::cout << "Reading phase input: " << phaseInput << std::endl;
    *r = phaseInput;
    phaseInput = -1;
  }
  else
  {
    //std::cout << "Reading from com: " << processorCom << std::endl;
    *r = processorCom;
  }
  
  proc->setPC(pc + 2);
}

void Day07::opOutput(IntProcessor* proc, int modes)
{
  int modeA = proc->getMode(modes, 0);

  int* pc = proc->getPC();
  int a = proc->resolveRead(pc + 1, modeA);
  //std::cout << "Writing to com: " << a << std::endl;
  processorCom = a;
  proc->setPC(pc + 2);
}
