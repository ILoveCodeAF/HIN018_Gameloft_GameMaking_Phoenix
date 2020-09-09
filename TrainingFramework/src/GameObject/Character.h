#pragma once

#include "DifferentlyAnimationSprite.h"
#include "U_Math.h"

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

private:
	std::shared_ptr<DifferentlyAnimationSprite> m_animations;
	int m_maxHP;
	int m_currentHP;
	int m_attackDamage;

};