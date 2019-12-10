#include "AbstractDay.h"
#include <iostream>
#include <fstream>
#include <streambuf>

template<typename T>
AbstractDay<T>::AbstractDay(const char* inputFileName) : m_inputFileName(inputFileName)
{
}

template<typename T>
std::string AbstractDay<T>::getInput()
{
  std::fstream fileStream(this->m_inputFileName.c_str());
  std::string fileContent((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));

  return fileContent;
}

template<typename T>
void AbstractDay<T>::runDay()
{
  std::string input = getInput();
  T* parsedInput = parseInput(input);
  runPart1(parsedInput);
  delete parsedInput;

  input = getInput();
  parsedInput = parseInput(input);
  runPart2(parsedInput);
  delete parsedInput;
}
