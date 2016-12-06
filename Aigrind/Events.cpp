#include "stdafx.h"
#include "Events.h"
#include "Object.h"

UpdatableHandler::UpdatableHandler(UpdatableCallback *callback)
{
  //auto callback = dynamic_cast<DestroyableObject *>(this);
  //if (callback != nullptr)
  callback->add(this);
}

void UpdatableCallback::add(UpdatableHandler *updatable)
{
  m_updatables.push_back(updatable);
}

void UpdatableCallback::onUpdate(float delta)
{
  for (auto it = m_updatables.begin(); it != m_updatables.end(); ++it)
    (*it)->onUpdatableTic(delta);
}