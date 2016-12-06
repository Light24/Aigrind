#pragma once

#include <windows.h>
#include <d2d1.h>

#include <map>
#include "GraphycalBody.h"
#include "PhysicalBody.h"


class GraphycalBody;
class PhysicalBody;

// Объединяет в себе функции менеджера физической и графической частей
class EngineManager
{
public:
  static EngineManager *instance();
  static EngineManager *initialize(HWND hwnd);

private:
  EngineManager(HWND hwnd);
  EngineManager(const EngineManager &);
  EngineManager &operator=(const EngineManager &);
  ~EngineManager();

private:
  const float GRAVITY = 9.8;
  static EngineManager *m_instance;
  std::map<int, PhysicalBody *> m_physicals;
  std::map<int, GraphycalBody *> m_graphycals;

  ID2D1HwndRenderTarget *m_pRT;
  RECT m_client_rect;

  ULONGLONG m_last_draw_time;
  ULONGLONG m_last_update_time;

public:
  void add(PhysicalBody *body);
  void add(GraphycalBody *body);

  void remove(PhysicalBody *body);
  void remove(GraphycalBody *body);

  const RECT &getWindowSize() const;

  void update();

private:
  void draw();
  void update(float delta);
};

