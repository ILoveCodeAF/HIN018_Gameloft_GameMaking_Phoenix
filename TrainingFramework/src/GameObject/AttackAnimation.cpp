#include "AttackAnimation.h"

extern int screenHeight;

AttackAnimation::AttackAnimation(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int dmg, Vector2 direction, float duration):
	DifferentlyAnimationSprite(model, shader, texture), m_direction(direction), m_duration(duration), m_damage(dmg)
{}

AttackAnimation::~AttackAnimation()
{}

void AttackAnimation::Update(float deltaTime)
{
	if (Alive())
	{
		m_Vec2DPos.x = m_x;
		m_Vec2DPos.y = m_y;
		m_Vec2DPos += m_direction * deltaTime;
		m_x = m_Vec2DPos.x;
		m_y = m_Vec2DPos.y;
		Set2DPosition(m_x, m_y-m_currentAnimation->m_height[m_currentFrame] / 2);
		m_duration -= deltaTime;

		if (m_x < 0 || m_x > screenHeight)
		{
			m_duration = -1.0f;
		}
	}
	
}

bool AttackAnimation::Alive()
{
	return m_duration > 0.0f;
}

void AttackAnimation::SetDuration(float duration)
{
	m_duration = duration;
}

void AttackAnimation::SetDirection(int x, int y)
{
	m_direction = Vector2(x, y);
}

AttackAnimation AttackAnimation::Clone()
{
	return *this;
}

int AttackAnimation::GetDamage()
{
	return m_damage;
}
