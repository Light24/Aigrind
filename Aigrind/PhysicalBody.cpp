#include "stdafx.h"
#include "PhysicalBody.h"


PhysicalBody::PhysicalBody(Object *owner) : m_owner(owner)
{
}


PhysicalBody::~PhysicalBody()
{
}

void PhysicalBody::update(float delta)
{
  Vec2 pos = getPos();
  Vec2 velocity = getVelocity();
  setPos(velocity * delta + getPos());
}

void PhysicalBody::setVelocity(const Vec2 &velocity)
{
  m_velocity = velocity;
}

void PhysicalBody::setPos(const Vec2 &pos)
{
  m_pos = pos;
}

void PhysicalBody::setMass(const float &mass)
{
  m_mass = mass;
}

bool PhysicalBody::isStatic()
{
  return (getMass() == 0);
}

const Vec2 &PhysicalBody::getVelocity() const
{
  return m_velocity;
}

const Vec2 &PhysicalBody::getPos() const
{
  return m_pos;
}

const float &PhysicalBody::getMass() const
{
  return m_mass;
}

int PhysicalBody::getId()
{
  return (int) this;
}