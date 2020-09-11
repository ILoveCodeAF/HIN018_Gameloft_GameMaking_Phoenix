#pragma once

class HitBox
{
public:
	HitBox(int x, int y, int w, int h, int dmg, float duration, bool ofEnermy = false);
	~HitBox();
	int GetDamage();
	void Expire();
	bool DetectCollision(int x, int y, int w, int h);
	void Update(float deltaTime);
	bool IsAlive();
private:
	int m_x, m_y, m_w, m_h;
	int m_dmg;
	float m_duration;
	bool m_ofEnermy;
	bool m_alive;
};