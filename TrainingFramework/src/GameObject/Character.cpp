#include "Character.h"

Character::Character()
{
}

Character::Character(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int maxHP, int attackDamage):
	m_maxHP(maxHP), m_attackDamage(attackDamage), m_currentHP(maxHP), m_x(1000/2), m_y(496/3)
{
	m_animations = std::make_shared<DifferentlyAnimationSprite>(model, shader, texture);
	m_animations->Set2DPosition(m_x, m_y);
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
	m_animations->Draw();
}

void Character::Update(GLfloat deltaTime)
{
	m_animations->Update(deltaTime, m_x, m_y);
}

void Character::Left(bool is_left)
{
	m_animations->Left(is_left);
}

void Character::Set2DPosition(int x, int y)
{
	m_animations->Set2DPosition(x, y);
}

void Character::Set2DPosition(Vector2 &vec)
{
	m_animations->Set2DPosition(vec);
}