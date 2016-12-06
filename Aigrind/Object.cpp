#include "stdafx.h"
#include "Object.h"


Object::Object(OBJECT_TYPES objectType) : m_object_type(objectType)
{

}

Object::~Object()
{
  EngineManager::instance()->remove(m_graphycal);
  EngineManager::instance()->remove(m_physical);
  delete m_graphycal;
  delete m_physical;
}

bool Object::checkRemove()
{
  return m_remove;
}

void Object::setRemove()
{
  m_remove = true;
}

void Object::update(float delta)
{
  UpdatableCallback::onUpdate(delta);
  onUpdate(delta);
}

void Object::setGraphycalBody(GraphycalBody *graphycal)
{
  m_graphycal = graphycal;
  EngineManager::instance()->add(m_graphycal);
}

void Object::setPhysicalBody(PhysicalBody *physical)
{
  m_physical = physical;
  EngineManager::instance()->add(m_physical);
}

GraphycalBody *Object::getGraphycalBody() const
{
  return m_graphycal;
}

PhysicalBody *Object::getPhysicalBody() const
{
  return m_physical;
}

int Object::getId()
{
  return (int) this;
}

const Vec2 &Object::getPos() const
{
  return getPhysicalBody()->getPos();
}

DestroyableObject::DestroyableObject(Object *object) : UpdatableHandler(object)
{

}

void DestroyableObject::onUpdatableTic(float delta)
{
  m_live_time += delta;

  if (m_live_time >= m_live_time_max)
  { 
    dynamic_cast<Object *>(this)->setRemove();
    onDestroy();
  }
}

void DestroyableObject::setLiveTime(float liveTime)
{
  m_live_time_max = liveTime;
}

float DestroyableObject::getLiveTime()
{
  return m_live_time;
}

float DestroyableObject::getLiveTimeMax()
{
  return m_live_time_max;
}

GunObject::GunObject(OBJECT_TYPES objectType) : Object(objectType)
{
  RECT wSize = EngineManager::instance()->getWindowSize();
  float size = 25;
  GraphycalBody *graphicalBody = new GraphycalBody(this, size);
  setGraphycalBody(graphicalBody);

  Vec2 pos = Vec2((wSize.right - size) / 2, wSize.bottom - size);
  PhysicalBody *physicalBody = new PhysicalBody(this);
  physicalBody->setPos(pos);
  setPhysicalBody(physicalBody);
}

void GunObject::onUpdate(float delta)
{
  m_shot_time_left += delta;
  
  if (rand() % 120 < m_shot_time_left)
  {
    shot();
    m_shot_time_left = 0;
  }
}

void GunObject::shot()
{
  BulletObject *object = (BulletObject*) ObjectManager::instance()->create(BULLET);
  object->initialize(this);
}

BulletObject::BulletObject(OBJECT_TYPES objectType) : Object(objectType), DestroyableObject(this)
{
}

void BulletObject::initialize(Object *parent)
{
  const int CONST_DEGREE = 90;

  RECT wSize = EngineManager::instance()->getWindowSize();
  float size = 6;
  GraphycalBody *graphicalBody = new GraphycalBody(this, size);
  setGraphycalBody(graphicalBody);


  Vec2 pos = parent->getPos();
  int deg = (rand() % SCATTER_DEGREE + (CONST_DEGREE - SCATTER_DEGREE)) * getRandomSign();
  Vec2 velocity = getPointOnRandomAngleLine(deg, MIN_VELOCITY, MAX_VELOCITY);
  velocity.y *= -1;

  PhysicalBody *physicalBody = new PhysicalBody(this);
  physicalBody->setPos(pos);
  physicalBody->setVelocity(velocity);
  physicalBody->setMass(8);
  setPhysicalBody(physicalBody);

  float liveTime = (MIN_LIVE_TIME + (static_cast<float>(rand()) / static_cast <float>(RAND_MAX / (MAX_LIVE_TIME - MIN_LIVE_TIME))));
  setLiveTime(liveTime);
}

void BulletObject::onUpdate(float delta)
{
}

void BulletObject::onDestroy()
{
  Object *object;

  for (int i = 0; i != CREATE_BULLET_SPLINTER_ON_DESTROY; ++i)
  {
    BulletSplinterObject *object = (BulletSplinterObject*)ObjectManager::instance()->create(BULLET_SPLINTER);
    object->initialize(this);
  }

  int sparkCount = rand() % CREATE_SPARKS_ON_DESTROY_MAX;
  for (int i = 0; i != sparkCount; ++i)
  {
    SparkObject *object = (SparkObject*)ObjectManager::instance()->create(SPARK);
    object->initialize(this);
  }
}

BulletSplinterObject::BulletSplinterObject(OBJECT_TYPES objectType) : Object(objectType), DestroyableObject(this)
{
}

void BulletSplinterObject::initialize(BulletObject *parent)
{
  RECT wSize = EngineManager::instance()->getWindowSize();
  float size = 4;
  GraphycalBody *graphicalBody = new GraphycalBody(this, size);
  setGraphycalBody(graphicalBody);

  Vec2 pos = parent->getPos();
  int deg = (rand() % SCATTER_DEGREE + (CONST_DEGREE - SCATTER_DEGREE)) * getRandomSign();

  const int SCALAR_VELOCITY_MAX = 10;
  Vec2 velocity = parent->getPhysicalBody()->getVelocity();
  velocity.x = velocity.x * 2 + (rand() % SCALAR_VELOCITY_MAX) / 2 * getRandomSign();
  velocity.x = velocity.x * 2 + (rand() % SCALAR_VELOCITY_MAX) / 2 * getRandomSign();

  PhysicalBody *physicalBody = new PhysicalBody(this);
  physicalBody->setPos(pos);
  physicalBody->setVelocity(velocity);
  physicalBody->setMass(3);
  setPhysicalBody(physicalBody);

  const int DIFFERENT_TIME_LIVE = 2;
  float liveTime = max(1, (parent->getLiveTime() / 2) + (rand() % DIFFERENT_TIME_LIVE) * getRandomSign());
  setLiveTime(liveTime);
}

void BulletSplinterObject::onUpdate(float delta)
{
}

void BulletSplinterObject::onDestroy()
{
  int sparkCount = rand() % CREATE_SPARKS_ON_DESTROY_MAX;
  for (int i = 0; i != sparkCount; ++i)
  {
    SparkObject *object = (SparkObject*)ObjectManager::instance()->create(SPARK);
    object->initialize(this);
  }
}

SparkObject::SparkObject(OBJECT_TYPES objectType) : Object(objectType), DestroyableObject(this)
{
}

void SparkObject::initialize(Object *parent)
{
  RECT wSize = EngineManager::instance()->getWindowSize();
  float size = 2;
  GraphycalBody *graphicalBody = new GraphycalBody(this, size);
  setGraphycalBody(graphicalBody);


  Vec2 pos = parent->getPos();
  Vec2 velocity;
  const int SCALAR_VELOCITY_MAX = 10;
  velocity.y = (1 + rand() % (SCALAR_VELOCITY_MAX / 2)) * dynamic_cast<DestroyableObject*>(parent)->getLiveTimeMax() * getRandomSign();
  velocity.x = (1 + rand() % (SCALAR_VELOCITY_MAX / 2)) * dynamic_cast<DestroyableObject*>(parent)->getLiveTimeMax() * getRandomSign();

  PhysicalBody *physicalBody = new PhysicalBody(this);
  physicalBody->setPos(pos);
  physicalBody->setVelocity(velocity);
  physicalBody->setMass(1);
  setPhysicalBody(physicalBody);

  const int DIFFERENT_TIME_LIVE = 2;
  float liveTime = max(1, (dynamic_cast<DestroyableObject*>(parent)->getLiveTime() / 2) + (rand() % DIFFERENT_TIME_LIVE) * getRandomSign());
  setLiveTime(liveTime);
}

void SparkObject::onUpdate(float delta)
{
}

void SparkObject::onDestroy()
{
}