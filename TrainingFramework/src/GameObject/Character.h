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
	void		loadAnimation(std::string path, float scale = 1.0f);
	void		SetAnimation(std::string animation_name);
	void		ResetAnimation(std::string animation_name);
	void		Draw();
	void		Update(GLfloat deltaTime);
	void		Left(bool is_left);
	void		Set2DPosition(int x, int y);
	void		Set2DPosition(Vector2&);
	void		SetPositionX(int x) { m_animations->SetPositionX(x); }
	void		SetPositionY(int y) { m_animations->SetPositionY(y); }
	void		HandleKey(int key);
	int			GetPositionX() { return m_animations->GetPositionX(); }
	int			GetPositionY() { return m_animations->GetPositionY(); }
	int			GetHeight() { return m_animations->GetHeight(); }
	int			GetWidth() { return m_animations->GetWidth(); }
	std::string	GetState() { return m_animations->GetState(); }
	bool		Alive() { return GetState() != DIE; }

	int			GetDirection() { return m_animations->GetDirection(); }
	float		GetJumpDuration() { return m_jumpDuration; }
	void		SetJumpDuration(float time) { m_jumpDuration = time; }
	bool		Attack() { return m_animations->GetCurrentFrame() == 0; }
	void		GotAttacked(int dmg);
	bool		Attacking() { return m_isAttacking; }
	void		SetStateAttacking(bool isAttacking) { m_isAttacking = isAttacking; }
	int			GetAttackDamage() { return m_attackDamage; }
	bool		JumpCauseDamage() { return m_jumpCauseDamage; }
	void		SetJumpCauseDamage(bool jumpcauseDamage) { m_jumpCauseDamage = jumpcauseDamage; }
	int			GetMaxHP() { return m_maxHP; }

private:
	std::shared_ptr<DifferentlyAnimationSprite> m_animations;
	std::shared_ptr<HPSprite> m_hpSprite;
	int m_maxHP;
	int m_currentHP;
	int m_attackDamage;
	float m_jumpDuration;
	bool m_jumpCauseDamage;
	bool m_isAttacking;

};