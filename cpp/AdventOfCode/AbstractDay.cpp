#include "AbstractDay.h"
#include <iostream>
#include <fstream>
#include <streambuf>

AbstractDay::AbstractDay(const char* inputFileName) : m_inputFileName(inputFileName)
{
}

std::string AbstractDay::getInput()
{
  std::fstream fileStream(this->m_inputFileName.c_str());
  std::string fileContent((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));

  std::cout << fileContent << std::endl;

  return fileContent;
}

void AbstractDay::runDay()
{
  std::string input = getInput();
  void* parsedInput = parseInput(input);
  runPart1(parsedInput);
  delete parsedInput;

  input = getInput();
  parsedInput = parseInput(input);
  runPart2(parsedInput);
  delete parsedInput;
}
