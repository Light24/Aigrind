#pragma once
#include <map>

#include "Object.h"
#include "defines.h"

class Object;

enum OBJECT_TYPES
{
  GUN,
  BULLET,
  BULLET_SPLINTER,
  SPARK,
};

// менеджер объектов сцены
class ObjectManager
{
public:
  static ObjectManager *instance();

private:
  static ObjectManager *m_instance;
  std::map<OBJECT_ID, Object *> m_objects;

private:
  ObjectManager();
  ~ObjectManager();

private:
  void add(Object *object);

public:
  Object *create(OBJECT_TYPES objectType);
  void remove(Object *object);
  void update(float delta);
};

