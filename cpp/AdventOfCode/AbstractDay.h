#pragma once
#include <string>

class AbstractDay
{
private:
  std::string m_inputFileName;

public:
  AbstractDay(const char* inputFileName);

  void runDay();
  std::string getInput();

  virtual void* parseInput(std::string& input) = 0;
  virtual void runPart1(void* input) = 0;
  virtual void runPart2(void* input) = 0;
};

