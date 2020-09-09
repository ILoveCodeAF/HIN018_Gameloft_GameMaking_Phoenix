#include "HPSprite.h"
#include "GameManager/ResourceManagers.h"


HPSprite::HPSprite(int maxHP):
	m_currentHP(maxHP), m_maxHP(maxHP)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("red");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	m_pSpriteCurrentHP = std::make_shared<Sprite2D>(model, shader, texture);
	
	
	texture = ResourceManagers::GetInstance()->GetTexture("white");
	m_pSpriteMaxHP = std::make_shared<Sprite2D>(model, shader, texture);
	m_pSpriteMaxHP->SetSize(20, 5);
}

HPSprite::~HPSprite()
{}

void HPSprite::Set2DPosition(int x, int y)
{
	m_pSpriteMaxHP->Set2DPosition(x, y);
	m_pSpriteCurrentHP->Set2DPosition(x - 10 + 20 * m_currentHP / m_maxHP / 2, y);
}

void HPSprite::Draw()
{
	m_pSpriteCurrentHP->SetSize(20*m_currentHP/m_maxHP, 5);
	m_pSpriteMaxHP->Draw();
	m_pSpriteCurrentHP->Draw();
}

void HPSprite::SetCurrentHP(int currentHP)
{
	m_currentHP = currentHP;
}

void HPSprite::SetMaxHP(int maxHP)
{
	m_maxHP = maxHP;
}

void HPSprite::Update()
{}