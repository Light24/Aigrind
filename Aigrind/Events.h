#pragma once

#include "stdafx.h"
#include <list>

class UpdatableCallback;

class UpdatableHandler
{
public:
  UpdatableHandler(UpdatableCallback *callback);
  virtual void onUpdatableTic(float delta) = 0;
};

class UpdatableCallback
{
private:
  std::list<UpdatableHandler *> m_updatables;

public:
  void add(UpdatableHandler *updatable);
  void onUpdate(float delta);
};