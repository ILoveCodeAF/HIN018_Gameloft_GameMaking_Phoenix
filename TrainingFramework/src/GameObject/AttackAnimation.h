#pragma once

#include "U_Math.h"
#include "DifferentlyAnimationSprite.h"

class AttackAnimation: public DifferentlyAnimationSprite
{
public:
	AttackAnimation(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int dmg, Vector2 direction, float duration);
	~AttackAnimation();
	void Update(float deltaTime) override;
	void SetDuration(float duration);
	void SetDirection(int x, int y);
	AttackAnimation Clone();
	bool Alive();
	int GetDamage();
private:
	float m_duration;
	Vector2 m_direction;
	int m_damage;

};