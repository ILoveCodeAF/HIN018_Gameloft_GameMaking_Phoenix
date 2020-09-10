#pragma once

#include "Sprite2D.h"
#include <memory.h>

class HPSprite
{
public:
	HPSprite(int maxHP);
	~HPSprite();
	void Set2DPosition(int x, int y);
	void Draw();
	void SetCurrentHP(int currentHP);
	void SetMaxHP(int maxHP);
	void Update(int currentHP);
private:
	int m_maxHP;
	int m_currentHP;
	int m_height;
	int m_width;
	std::shared_ptr<Sprite2D> m_pSpriteMaxHP;
	std::shared_ptr<Sprite2D> m_pSpriteCurrentHP;
};