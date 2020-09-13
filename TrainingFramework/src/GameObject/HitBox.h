#pragma once

#include "AnimationSprite.h"
#include "U_Math.h"

class HitBox
{
public:
	HitBox(int x, int y, int w, int h, int dmg, float duration, bool ofEnermy = false);
	~HitBox();
	int GetDamage();
	void Expire();
	bool DetectCollision(int x, int y, int w, int h);
	void Update(float deltaTime);
	void Draw();
	bool IsAlive();

	void loadAnimation(std::string name, int numFrames, int frameTime);
	void SetAnimation(std::shared_ptr<AnimationSprite> animation);
	void SetDirection(int x, int y);
	void SetDuration(float duration);
private:
	int m_x, m_y, m_w, m_h;
	int m_dmg;
	float m_duration;
	bool m_ofEnermy;
	//bool m_alive;

	std::shared_ptr<AnimationSprite> m_animation;
	float m_halfDuration;
	Vector2 m_direction;
	float time;
	int m_yClone;
};