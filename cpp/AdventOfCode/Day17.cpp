#include "Day17.h"
#include <vector>
#include <sstream>
#include <iostream>
#include "IntProcessor.h"

Day17::Day17() : AbstractDay("input/input17.txt")
{
}

void* Day17::parseInput(std::string& input)
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

void Day17::runPart1(void* input)
{
  std::vector<int>* vector = (std::vector<int>*)input;

  IntProcessor proc(vector->data(), vector->size(), 4096);
  int64_t output;
  proc.runProgram();
  char scaffolding[10240];
  unsigned int outputLength = 0;
  unsigned int lineLength = 0;
  while (proc.isOutputReady()) {
    proc >> output;
    scaffolding[outputLength++] = (char)output;
    if (output == 10 && lineLength == 0) {
      lineLength = outputLength;
    }
    std::cout << (char) output;
  }

  const int height = outputLength / lineLength;
  const int width = lineLength;

  int sum = 0;
  for (int y = 1; y < height - 1; y++) {
    for (int x = 1; x < width - 1; x++) {
      if (scaffolding[y * width + x] == '#'
        && scaffolding[(y + 1) * width + x] == '#'
        && scaffolding[(y - 1) * width + x] == '#'
        && scaffolding[y * width + x + 1] == '#'
        && scaffolding[y * width + x - 1] == '#') {
        sum += x * y;
      }
    }
  }

  std::cout << "Sum: " << sum << std::endl;
}

void Day17::runPart2(void* input)
{
}
