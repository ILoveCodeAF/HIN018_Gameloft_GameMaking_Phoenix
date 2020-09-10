#include "Character.h"

Character::Character()
{
}

Character::Character(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int maxHP, int attackDamage):
	m_maxHP(maxHP), m_attackDamage(attackDamage), m_currentHP(maxHP)
{
	m_animations = std::make_shared<DifferentlyAnimationSprite>(model, shader, texture);
	m_hpSprite = std::make_shared<HPSprite>(maxHP);
	m_jumpDuration = 0.0f;
}

Character::~Character()
{}

void Character::Init()
{
	m_animations->Init();
}

void Character::loadAnimation(std::string path)
{
	m_animations->loadAnimation(path);
}

void Character::SetAnimation(std::string animation_name)
{
	m_animations->SetAnimation(animation_name);
}

void Character::Draw()
{
	m_hpSprite->Draw();
	m_animations->Draw();
}

void Character::Update(GLfloat deltaTime)
{
	m_hpSprite->SetCurrentHP(m_currentHP);
	m_hpSprite->Set2DPosition(m_animations->GetPositionX(), m_animations->GetPositionY() - m_animations->GetHeight() - 10);
	m_animations->Update(deltaTime);
}

void Character::Left(bool is_left)
{
	m_animations->Left(is_left);
}

void Character::Set2DPosition(int x, int y)
{
	m_animations->SetPosition(x, y);
}

void Character::Set2DPosition(Vector2 &vec)
{
	m_animations->Set2DPosition(vec);
}

void Character::HandleKey(int key)
{
	m_animations->ChangeAnimation(key);
}

