#pragma once
#include "stdafx.h"
#include <math.h>

class Vec2
{
public:
  Vec2() : x(0), y(0)
  {

  }

  Vec2(float x, float y) : x(x), y(y)
  {

  }

  Vec2 operator*(const float &arg)
  {
    x *= arg;
    y *= arg;
    return *this;
  }

  Vec2 operator+(const Vec2 &arg)
  {
    x += arg.x;
    y += arg.y;
    return *this;
  }
  
public:
  float x;
  float y;
};


typedef int OBJECT_ID;

#define MIN_VELOCITY 160
#define MAX_VELOCITY 260

#define M_PI 3.14159265358979323846

inline double degToRad(float deg)
{
  return deg * M_PI / 180;
}

inline int getRandomSign()
{
  return rand() % 2 != 0 ? 1 : -1;
}

inline Vec2 getPointOnRandomAngleLine(double deg, float minDist, float maxDist)
{
  Vec2 point;
  double angle = degToRad(deg);
  // тагенс не должен быть равен 0, правильно делать конечно через возрат пользовтаельского исключения, его обработку в вызывающем коде, однако в нашем случае пойдет и так.
  while (tan(angle) == 0)
  {
    deg += getRandomSign() * 1;
    angle = degToRad(deg);
  }
  float maxDistY = maxDist / sqrt(1 + 1 / (tan(angle) * tan(angle)));
  float minDistY = minDist / sqrt(1 + 1 / (tan(angle) * tan(angle)));

  point.y = (minDistY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxDistY - minDistY))));
  point.x = (point.y / tan(angle));

  return point;
}