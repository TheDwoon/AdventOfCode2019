#include "IntProcessor.h"
#include <math.h>

void IntProcessor::runProgram()
{
}

void IntProcessor::runInstruction()
{
}

int IntProcessor::getDigit(int x, int digit)
{
  int e = static_cast<int>(pow(10, digit));
  return (x / e) % 10;
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
  case 1:
    return m_memory + *addr;
  default:
    return nullptr;
  }
}
