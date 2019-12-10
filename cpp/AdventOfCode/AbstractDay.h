#pragma once
#include <string>

template<typename T>
class AbstractDay
{
private:
  std::string m_inputFileName;

public:
  AbstractDay(const char* inputFileName);

  void runDay();
  std::string getInput();

  virtual T* parseInput(std::string& input) = 0;
  virtual void runPart1(T* input) = 0;
  virtual void runPart2(T* input) = 0;
};

