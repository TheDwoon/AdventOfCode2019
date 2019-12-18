#include "Day10.h"
#include <iostream>
#include <algorithm>
#include <math.h>

struct Target {
  Target(float angle, float distance, Location loc) : angle(angle), location(loc), distance(distance) {}
  float angle;
  float distance;
  Location location;
};

//std::vector<Target>::iterator findTarget(std::vector<Target>::iterator start, std::vector<Target>::iterator end,
//    std::vector<Target>::iterator current) {
//  float currentAngle = (*current).angle;
//  while ((*current).destroyed || (*current).angle == currentAngle)
//  {
//    ++current;
//    if (current == end)
//      current = start;
//  }
//
//  return current;
//}

Day10::Day10() : AbstractDay("input/input10.txt")
{
}

void* Day10::parseInput(std::string& input)
{
  std::vector<Location>* locations = new std::vector<Location>();

  int x = 0;
  int y = 0;
  for (int i = 0; i < input.size(); i++)
  {
    char& c = input.at(i);
    if (c == '#')
    {
      locations->push_back(Location(x, y));
      x++;
    }
    else if (c == '.')
    {
      x++;
    }
    else if (c == '\n')
    {
      y++;
      x = 0;
    }
  }

  return locations;
}

void Day10::runPart1(void* input)
{
  std::vector<Location>* locations = (std::vector<Location>*)input;

  Location bestLocation(0, 0);
  int bestScore = 0;
  for (std::vector<Location>::iterator it = locations->begin(); it != locations->end(); ++it)
  {
    Location& loc = *it;
    int score = evaluateLocation(loc, locations);
    if (bestScore < score)
    {
      bestScore = score;
      bestLocation = loc;
    }
  }

  std::cout << "Best Location (" << bestLocation.x << ", " << bestLocation.y << ") with "
    << bestScore << " visible asteroids" << std::endl;
}

void Day10::runPart2(void* input)
{
  std::vector<Location>* locations = (std::vector<Location>*)input;

  Location bestLocation(0, 0);
  int bestScore = 0;
  for (std::vector<Location>::iterator it = locations->begin(); it != locations->end(); ++it)
  {
    Location& loc = *it;
    int score = evaluateLocation(loc, locations);
    if (bestScore < score)
    {
      bestScore = score;
      bestLocation = loc;
    }
  }

  std::vector<Target> targets;
  for (std::vector<Location>::iterator it = locations->begin(); it != locations->end(); ++it)
  {
    Location& loc = *it;
    if (loc.x == bestLocation.x && loc.y == bestLocation.y)
      continue;

    float dX = loc.x - bestLocation.x;
    float dY = loc.y - bestLocation.y;
    float angle = atan2(dY, dX);
    targets.push_back(Target(angle, dX * dX + dY * dY, loc));
  }

  std::sort(targets.rbegin(), targets.rend(), [](Target& a, Target& b) -> bool { return a.angle < b.angle; });
  std::sort(targets.begin(), targets.end(), [](Target& a, Target& b) -> bool { return a.distance < b.distance; });

  for (int i = 0; i < targets.size(); i++) {
    Target& t = targets.at(i);
    std::cout << i << ")" << t.angle << ", " << t.distance
      << " (" << t.location.x << ", " << t.location.y << ")" << std::endl;
  }

  Location& loc = targets.at(199).location;
  std::cout << "Code: " << loc.x * 100 + loc.y << std::endl;
}

int Day10::evaluateLocation(Location& location, std::vector<Location>* locations)
{
  std::vector<float> angles;
  for (int i = 0; i < locations->size(); i++)
  {
    Location& loc = locations->at(i);
    if (loc.x == location.x && loc.y == location.y)
      continue;

    float currentAngle = atan2(location.y - loc.y, location.x - loc.x);
    if (std::find(angles.begin(), angles.end(), currentAngle) == angles.end())
      angles.push_back(currentAngle);
  }

  return angles.size();
}
