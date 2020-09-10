#pragma once

#include "DifferentlyAnimationSprite.h"
#include "U_Math.h"
#include "HPSprite.h"

class Character
{
public:
	Character();
	Character(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int maxHP, int attackDamage);
	~Character();

	void		Init();
	void		loadAnimation(std::string path);
	void		SetAnimation(std::string animation_name);
	void		Draw();
	void		Update(GLfloat deltaTime);
	void		Left(bool is_left);
	void		Set2DPosition(int x, int y);
	void		Set2DPosition(Vector2&);
	void		HandleKey(int key);
	int			GetPositionX() { return m_animations->GetPositionX(); }
	int			GetPositionY() { return m_animations->GetPositionY(); }
	int			GetHeight() { return m_animations->GetHeight(); }
	int			GetWidth() { return m_animations->GetWidth(); }
	std::string	GetState() { return m_animations->GetState(); }

	int			GetDirection() { return m_animations->GetDirection(); }
	float		GetJumpDuration() { return m_jumpDuration; }
	void		SetJumpDuration(float time) { m_jumpDuration = time; }
	bool		IsKick() { return m_animations->GetCurrentFrame() == 0; }
	void		GotAttacked(int dmg) { m_currentHP = m_currentHP > dmg ? m_currentHP - dmg : 0; }

private:
	std::shared_ptr<DifferentlyAnimationSprite> m_animations;
	std::shared_ptr<HPSprite> m_hpSprite;
	int m_maxHP;
	int m_currentHP;
	int m_attackDamage;
	float m_jumpDuration;

};