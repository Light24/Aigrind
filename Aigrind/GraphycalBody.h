#pragma once
#include "stdafx.h"

#include "Object.h"
#include <d2d1.h>

class Object;

class GraphycalBody
{
public:
  GraphycalBody(const Object *const owner, float size);
  ~GraphycalBody();

private:
  GraphycalBody(const GraphycalBody &);
  GraphycalBody &operator=(const GraphycalBody &);
  
private:
  const Object *const m_owner;
  float m_size;

public:
  float getSize();
  void draw(ID2D1SolidColorBrush *pBlackBrush, ID2D1HwndRenderTarget *m_pRT);
  int getId();
};

