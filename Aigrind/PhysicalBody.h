#pragma once

#include "defines.h"
#include "Object.h"


class PhysicalBody
{
public:
  PhysicalBody(Object *owner);
  ~PhysicalBody();

private:
  Object *m_owner;
  Vec2 m_pos;
  Vec2 m_velocity;
  float m_mass;

public:
  void setVelocity(const Vec2 &velocity);
  void setPos(const Vec2 &pos);
  void setMass(const float &mass);

  bool isStatic();
  const Vec2 &getVelocity() const;
  const Vec2 &getPos() const;
  const float &getMass() const;

  void update(float delta);
  int getId();

};

