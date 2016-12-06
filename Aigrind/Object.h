#pragma once
#include "stdafx.h"

#include "ObjectManager.h"
#include "EngineManager.h"
#include "GraphycalBody.h"
#include "PhysicalBody.h"
#include "Events.h"

enum OBJECT_TYPES;
class GraphycalBody;

class Object : public UpdatableCallback
{
public:
  Object(OBJECT_TYPES objectType);
  virtual ~Object();

private:
  Object(const Object &);
  Object& operator=(const Object &);

public:
  bool checkRemove();
  void setRemove();
  void update(float delta);
  virtual void onUpdate(float delta) = 0;

  void setGraphycalBody(GraphycalBody *graphycal);
  void setPhysicalBody(PhysicalBody *physical);

  GraphycalBody *getGraphycalBody() const;
  PhysicalBody *getPhysicalBody() const;

  int getId();

  const Vec2 &getPos() const;

private:
  bool m_remove;
  GraphycalBody *m_graphycal;
  PhysicalBody *m_physical;
  OBJECT_TYPES m_object_type;
};

class DestroyableObject : public UpdatableHandler
{
public:
  DestroyableObject(Object *object);

private:
  float m_live_time_max;
  float m_live_time;

public:
  void onUpdatableTic(float delta) override;
  virtual void onDestroy() = 0;

  void setLiveTime(float liveTime);
  float getLiveTime();
  float getLiveTimeMax();
};

class GunObject : public Object
{
public:
  GunObject(OBJECT_TYPES objectType);

private:
  float m_shot_time_left;

public:
  virtual void onUpdate(float delta) override;
  void shot();
};

class BulletObject : public Object, public DestroyableObject
{
public:
  BulletObject(OBJECT_TYPES objectType);
  void initialize(Object *parent);

private:
  const float MIN_LIVE_TIME = 2;
  const float MAX_LIVE_TIME = 4;

  const int SCATTER_DEGREE = 30;

  const int CREATE_BULLET_SPLINTER_ON_DESTROY = 2;
  const int CREATE_SPARKS_ON_DESTROY_MAX = 20;

public:
  virtual void onUpdate(float delta) override;
  virtual void onDestroy() override;
};

class BulletSplinterObject : public Object, public DestroyableObject
{
public:
  BulletSplinterObject(OBJECT_TYPES objectType);
  void initialize(BulletObject *parent);

private:
  const int CREATE_SPARKS_ON_DESTROY_MAX = 20;
  const int CONST_DEGREE = 90;
  const int SCATTER_DEGREE = 45;

public:
  virtual void onUpdate(float delta) override;
  virtual void onDestroy() override;
};

class SparkObject : public Object, public DestroyableObject
{
public:
  SparkObject(OBJECT_TYPES objectType);
  void initialize(Object *parent);

public:
  virtual void onUpdate(float delta) override;
  virtual void onDestroy() override;
};