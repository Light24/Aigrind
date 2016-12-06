#include "stdafx.h"
#include "EngineManager.h"


EngineManager *EngineManager::m_instance;

EngineManager *EngineManager::initialize(HWND hwnd)
{
  if (m_instance == nullptr)
    m_instance = new EngineManager(hwnd);

  return m_instance;
}

EngineManager *EngineManager::instance()
{
  return m_instance;
}

EngineManager::EngineManager(HWND hwnd) : m_last_draw_time(GetTickCount64()), m_last_update_time(GetTickCount64())
{
  ID2D1Factory *pd2Factory = nullptr;
  HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pd2Factory);

  GetClientRect(hwnd, &m_client_rect);

  m_pRT = nullptr;
  hr = pd2Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(m_client_rect.right - m_client_rect.left, m_client_rect.bottom - m_client_rect.top)), &m_pRT);

  if (!SUCCEEDED(hr))
  {
  }
}


EngineManager::~EngineManager()
{
}


void EngineManager::add(PhysicalBody *body)
{
  m_physicals[body->getId()] = body;
}

void EngineManager::add(GraphycalBody *body)
{
  m_graphycals[body->getId()] = body;
}

void EngineManager::remove(PhysicalBody *body)
{
  m_physicals.erase(m_physicals.find(body->getId()));
}

void EngineManager::remove(GraphycalBody *body)
{
  m_graphycals.erase(m_graphycals.find(body->getId()));
}

const RECT &EngineManager::getWindowSize() const
{
  return m_client_rect;
}

void EngineManager::update()
{
  ULONGLONG time = GetTickCount64();

  float delta = (time - m_last_update_time) / 1000.f;
  update(delta);
  ObjectManager::instance()->update(delta);
  m_last_update_time = time;

  if (m_last_draw_time + 1000 / 60 <= time)
  {
    draw();
    m_last_draw_time += 1000 / 60;
  }
}

void EngineManager::update(float delta)
{
  for (auto it = m_physicals.begin(); it != m_physicals.end(); ++it)
  {
    PhysicalBody *body = (*it).second;
    if (body->isStatic())
      continue;

    Vec2 velocity = body->getVelocity();
    velocity.y += delta * GRAVITY * body->getMass();
    body->setVelocity(velocity);

    body->update(delta);
  }
}

void EngineManager::draw()
{
  ID2D1SolidColorBrush *pBlackBrush = NULL;

  static int a = 1;
  a += 1;
  m_pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &pBlackBrush);

  m_pRT->BeginDraw();
  m_pRT->Clear(D2D1::ColorF(D2D1::ColorF::Black));

  for (auto it = m_graphycals.begin(); it != m_graphycals.end(); ++it)
    (*it).second->draw(pBlackBrush, m_pRT);

  //m_pRT->DrawRectangle(D2D1::RectF(m_client_rect.left + a, m_client_rect.top, m_client_rect.right - 100.f, m_client_rect.bottom - 100.f), pBlackBrush);
  m_pRT->EndDraw();
}
