#include "stdafx.h"
#include "ObjectManager.h"


ObjectManager *ObjectManager::m_instance;

ObjectManager *ObjectManager::instance()
{
  if (m_instance == nullptr)
    m_instance = new ObjectManager();

  return m_instance;
}


ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}


void ObjectManager::add(Object *object)
{
  m_objects[object->getId()] = object;
}

Object *ObjectManager::create(OBJECT_TYPES objectType)
{
  Object *object = nullptr;

  switch (objectType)
  {
    case GUN:
    {
      object = new GunObject(objectType);
      break;
    }
    case BULLET:
    {
      object = new BulletObject(objectType);
      break;
    }
    case BULLET_SPLINTER:
    {
      object = new BulletSplinterObject(objectType);
      break;
    }
    case SPARK:
    {
      object = new SparkObject(objectType);
      break;
    }
  }
  if (object != nullptr)
    add(object);

  return object;
}

void ObjectManager::remove(Object *object)
{
  m_objects.erase(m_objects.find(object->getId()));
}

void ObjectManager::update(float delta)
{
  auto it = m_objects.begin();;
  while (it != m_objects.end())
  {
    auto itNext = it;
    ++itNext;

    Object *object = (*it).second;
    object->update(delta);
    if (object->checkRemove())
    {
      ObjectManager::instance()->remove(object);
      delete object;
    }

    it = itNext;
  }
}