#include "Day08.h"
#include <iostream>

#define IMG_WIDTH 25
#define IMG_HEIGHT 6
#define BLACK_CHAR ' '
#define WHITE_CHAR '#'
#define VOID_CHAR '0'

Day08::Day08() : AbstractDay("input/input08.txt")
{
}

void* Day08::parseInput(std::string& input)
{
  std::vector<int>* vector = new std::vector<int>();
  for (int i = 0; i < input.size(); i++)
  {
    char c = input[i];
    int num = c - '0';
    vector->push_back(num);
  }

	return vector;
}

void Day08::runPart1(void* input)
{
  std::vector<int>* vector = (std::vector<int>*)input;

  int numImages = vector->size() / (IMG_WIDTH * IMG_HEIGHT);

  histogram* hist = new histogram[numImages];
  int fewest0 = 0;
  for (int i = 0; i < numImages; i++) {
    hist[i] = countNumbersInLayer(vector, i);

    if (hist[i].occurences[0] < hist[fewest0].occurences[0])
    {
      fewest0 = i;
    }
  }

  int code = hist[fewest0].occurences[1] * hist[fewest0].occurences[2];
  std::cout << "fewest zeros: " << fewest0 << " code: " << code << std::endl;
}

void Day08::runPart2(void* input)
{
  std::vector<int>* vector = (std::vector<int>*)input;

  for (int y = 0; y < IMG_HEIGHT; y++)
  {
    for (int x = 0; x < IMG_WIDTH; x++)
    {
      std::cout << composeImage(vector, x, y) << " ";
    }

    std::cout << std::endl;
  }
}

histogram Day08::countNumbersInLayer(std::vector<int>* data, int layer)
{
  histogram h;

  int start = IMG_HEIGHT * IMG_WIDTH * layer;
  int end = IMG_HEIGHT * IMG_WIDTH * (layer + 1);

  for (int i = start; i < end; i++) {
    h.occurences[(*data)[i]]++;
  }

  return h;
}

char Day08::composeImage(std::vector<int>* data, int x, int y)
{
  int numLayers = data->size() / (IMG_WIDTH * IMG_HEIGHT);

  for (int layer = 0; layer < numLayers; layer++)
  {
    int layerOffset = IMG_WIDTH * IMG_HEIGHT * layer;
    int layerValue = (*data)[layerOffset + y * IMG_WIDTH + x];
    if (layerValue == 0)
      return BLACK_CHAR;
    else if (layerValue == 1)
      return WHITE_CHAR;
  }

  return VOID_CHAR;
}
