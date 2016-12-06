#include "stdafx.h"
#include "GraphycalBody.h"


GraphycalBody::GraphycalBody(const Object *const owner, float size) : m_owner(owner), m_size(size)
{
}


GraphycalBody::~GraphycalBody()
{
}

void GraphycalBody::draw(ID2D1SolidColorBrush *pBlackBrush, ID2D1HwndRenderTarget *m_pRT)
{
  Vec2 pos = m_owner->getPos();
  m_pRT->DrawRectangle(D2D1::RectF(pos.x - getSize(), pos.y - getSize(), pos.x + getSize(), pos.y + getSize()), pBlackBrush);
}

float GraphycalBody::getSize()
{
  return m_size;
}

int GraphycalBody::getId()
{
  return (int) this;
}