#pragma once
#include "AbstractDay.h"
#include <vector>

struct histogram {
  int occurences[3] = {0, 0, 0};
};

class Day08 : public AbstractDay
{
public:
  Day08();

  void* parseInput(std::string& input) override;
  void runPart1(void* input) override;
  void runPart2(void* input) override;

private:
  histogram countNumbersInLayer(std::vector<int>* data, int layer);
  char composeImage(std::vector<int>* data, int x, int y);
};

