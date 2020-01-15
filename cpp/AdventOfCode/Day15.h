#pragma once
#include "AbstractDay.h"
#include <vector>
#include <deque>

struct Map {
  unsigned int width;
  unsigned int height;
  short* data;
  short* pathing;

  Map(int width, int height) {
    this->width = width;
    this->height = height;
    data = new short[width * height];
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        data[y * width + x] = 3;
      }
    }

    pathing = new short[width * height];
    clearPathing();
  }

  ~Map() {
    delete[] data;
  }

  short get(int x, int y) {
    return data[y * width + x];
  }

  void set(int x, int y, short value) {
    data[y * width + x] = value;
  }

  short getPathing(int x, int y) {
    return pathing[y * width + x];
  }

  void setPathing(int x, int y, short value) {
    pathing[y * width + x] = value;
  }

  void clearPathing() {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        pathing[y * width + x] = SHRT_MAX;
      }
    }
  }
};

class Day15 : public AbstractDay
{
public:
  Day15();

  void* parseInput(std::string& input) override;
  void runPart1(void* input) override;
  void runPart2(void* input) override;

private:
  void printMap(Map& map);
  void printPath(Map& map);
  std::deque<short> findPath(Map& map, int sX, int sY, int searchedObject);
};

