#include "HitBox.h"

HitBox::HitBox(int x, int y, int w, int h, int dmg, float duration, bool OfEnermy):
	m_x(x), m_y(y), m_w(w), m_h(h), m_dmg(dmg), m_duration(duration), m_ofEnermy(OfEnermy)
{}

HitBox::~HitBox()
{}

int HitBox::GetDamage()
{
	return m_dmg;
}

void HitBox::Expire()
{
	m_duration = -1.0f;
}

bool HitBox::DetectCollision(int x, int y, int w, int h)
{
	if (m_x > x + w)
		return false;
	if (m_x + m_w < x)
		return false;
	if (m_y < y - h)
		return false;
	if (m_y - m_h > y)
		return false;
	return true;
}

void HitBox::Update(float deltaTime)
{
	m_duration -= deltaTime;
}

bool HitBox::IsAlive()
{
	return m_duration > 0.0f;
}